#include "state_data_manager.h"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "tag_map.h"




lv_obj_t* active_page = NULL;
lv_obj_t* old_page = NULL;
page_state_t current_page_state = PAGE_MAIN;
page_state_t next_page_state = PAGE_MAIN;

tag_map_t map = {0};
room_data_t bedroom = {0};
app_data_t data = {0};
app_data_t data_snapshot = {0};
settings_t settings = {0};


wifi_config_t wifi_config;
esp_mqtt_client_config_t mqtt_cfg;

SemaphoreHandle_t data_mutex;
SemaphoreHandle_t reconnect_sem;

void init_app_data()
{
    data_mutex = xSemaphoreCreateMutex();
    reconnect_sem = xSemaphoreCreateBinary();
    data.bedroom = &bedroom;
}
void init_network_data()
{
    esp_wifi_get_config(WIFI_IF_STA, &wifi_config);
    snprintf(settings.wifi_ssid, sizeof(settings.wifi_ssid), "%s", (char*)wifi_config.sta.ssid);
    snprintf(settings.wifi_pass, sizeof(settings.wifi_pass), "%s", (char*)wifi_config.sta.password);


    snprintf(settings.mqtt_address, sizeof(settings.mqtt_address), "%s", get_broker_address());
}

void init_app_data_handlers()
{
    tag_map_insert(&map, "home/bedroom/sensor/veml7700/data", bedroom_sensor_veml770_data_handler);
    tag_map_insert(&map, "home/bedroom/sensor/sht41/data", bedroom_sensor_sht41_data_handler);
}
void init_data()
{
    init_app_data();
    init_network_data();
    init_app_data_handlers();
    
}

app_data_t* get_data_snapshot()
{
    xSemaphoreTake(data_mutex, portMAX_DELAY);

    data_snapshot = data;

    xSemaphoreGive(data_mutex);

    return &data_snapshot;
}



void page_switcher_set_page_state(page_state_t next)
{
    next_page_state = next;
}

void set_page_home(lv_event_t *e)
{
    (void)e;
    page_switcher_set_page_state(PAGE_MAIN);
    ESP_LOGI("STATE_DATA_MANAGER", "Switching to Home page");
}

void set_page_settings(lv_event_t *e)
{
    (void)e;
    page_switcher_set_page_state(PAGE_SETTINGS);
    ESP_LOGI("STATE_DATA_MANAGER", "Switching to Settings page");
}
void set_page_climate(lv_event_t *e)
{
    (void)e;
    page_switcher_set_page_state(PAGE_CLIMATE);
    ESP_LOGI("STATE_DATA_MANAGER", "Switching to Climate page");
}

void set_page_lighting(lv_event_t *e)
{
    (void)e;
    page_switcher_set_page_state(PAGE_LIGHTING);
    ESP_LOGI("STATE_DATA_MANAGER", "Switching to Lighting page");
}

void load_new_page()
{
    ui_build_snapshot = get_data_snapshot();
    if (current_page_state != next_page_state) {
        current_page_state = next_page_state;
        lv_obj_delete(get_keyboard());
        switch (current_page_state) {
            case PAGE_MAIN:
                old_page = active_page;
                active_page = build_page(main_page, build_main_page);
                lv_screen_load(active_page);
                lv_obj_delete(old_page);
                break;
            case PAGE_SETTINGS:
                old_page = active_page;
                active_page = build_page(settings_page, build_settings_page);
                lv_screen_load(active_page);
                lv_obj_delete(old_page);
                break;
            case PAGE_CLIMATE:
                old_page = active_page;
                active_page = build_page(climate_page, build_climate_page);
                lv_screen_load(active_page);
                lv_obj_delete(old_page);
                break;
            case PAGE_LIGHTING:
                old_page = active_page;
                active_page = build_page(lighting_page, build_lighting_page);
                lv_screen_load(active_page);
                lv_obj_delete(old_page);
                break;
        }
        ESP_LOGI("STATE_DATA_MANAGER", "Page switched to: %d", current_page_state);
    }

    uint32_t inactive_time = lv_display_get_inactive_time(NULL);

    if(inactive_time > UI_INACTIVITY_TIMEOUT)
    {
        if(current_page_state != next_page_state)
            lv_obj_delete(get_keyboard());
        switch (current_page_state) {
            case PAGE_MAIN:
                old_page = active_page;
                active_page = build_page(main_page, build_main_page);
                lv_screen_load(active_page);
                lv_obj_delete(old_page);
                break;
            case PAGE_SETTINGS:
                old_page = active_page;
                active_page = build_page(settings_page, build_settings_page);
                lv_screen_load(active_page);
                lv_obj_delete(old_page);
                break;
            case PAGE_CLIMATE:
                old_page = active_page;
                active_page = build_page(climate_page, build_climate_page);
                lv_screen_load(active_page);
                lv_obj_delete(old_page);
                break;
            case PAGE_LIGHTING:
                old_page = active_page;
                active_page = build_page(lighting_page, build_lighting_page);
                lv_screen_load(active_page);
                lv_obj_delete(old_page);
                break;
        }
        lv_display_trigger_activity(NULL);
    }
}


void run_task(void *arg)
{
    (void)arg;

    
    init_data();

    ESP_LOGI("STATE_DATA_MANAGER", "System initialized successfully");

    ui_build_snapshot = get_data_snapshot();
    active_page = build_page(main_page, build_main_page);
    lv_screen_load(active_page);
    while (1) {
        
        load_new_page();

        
    
        vTaskDelay(pdMS_TO_TICKS(100));

        
    }
}

void data_manager_process_message(mqtt_q_message_t *msg)
{
    // Implementation for processing MQTT messages
    dispatch_tag(&map, &data, msg->topic, msg->payload, msg->payload_len);
}

void data_task(void *arg)
{
    (void)arg;

    mqtt_q_message_t msg;

    while(1)
    {
        if(xQueueReceive(data_queue, &msg, portMAX_DELAY) == pdTRUE)
            data_manager_process_message(&msg);
    }
}

void refresh_task(void *arg)
{
    while(1)
    {
        old_page = active_page;
        active_page = build_page(main_page, build_main_page);
        lv_screen_load(active_page);
        lv_obj_delete(old_page);

        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}

void network_task(void *arg)
{
    while(1)
    {
        if(xSemaphoreTake(reconnect_sem, portMAX_DELAY) == pdTRUE)
        {
            wifi_config_t cfg = {0};
            snprintf((char*)cfg.sta.ssid, sizeof(cfg.sta.ssid), "%s", settings.wifi_ssid);
            snprintf((char*)cfg.sta.password, sizeof(cfg.sta.password), "%s", settings.wifi_pass);

            esp_wifi_disconnect();
            ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &cfg));
            esp_wifi_connect();

            ESP_ERROR_CHECK(esp_mqtt_client_disconnect(get_client()));
            ESP_ERROR_CHECK(esp_mqtt_client_set_uri(get_client(), settings.mqtt_address));

            ESP_ERROR_CHECK(esp_mqtt_client_reconnect(get_client()));
        }
    }
}

void bedroom_sensor_veml770_data_handler(app_data_t *data, const char* payload, uint32_t length)
{
    // add logs 
    ESP_LOGI("veml7700", "Calling Handler");
    if(data == NULL || payload == NULL || length == 0)
        return;
    cJSON *root = cJSON_ParseWithLength(payload, length);

    if(root == NULL)
        return;
    
    cJSON *lux_value = cJSON_GetObjectItemCaseSensitive(root, "lux");

    if(cJSON_IsNumber(lux_value))
    {
        ESP_LOGI("veml7700_data_handler", "Data Received");
        data->bedroom->lux = (float)lux_value->valuedouble;
    }
    cJSON_Delete(root);
}

void bedroom_sensor_sht41_data_handler(app_data_t *data, const char* payload, uint32_t length)
{
    // add logs 
    ESP_LOGI("sht41", "Calling Handler");
    if(data == NULL || payload == NULL || length == 0)
        return;
    cJSON *root = cJSON_ParseWithLength(payload, length);

    if(root == NULL)
        return;
    
    cJSON *temp_value = cJSON_GetObjectItemCaseSensitive(root, "temp");
    cJSON *hum_value = cJSON_GetObjectItemCaseSensitive(root, "hum");
    ESP_LOGI("sht41_data_handler", "Data Received");

    if(cJSON_IsNumber(temp_value))
    {
        data->bedroom->temp = (float)temp_value->valuedouble;
    }
    if(cJSON_IsNumber(temp_value))
    {
        ESP_LOGI("sht41_data_handler", "Data Received");
        data->bedroom->hum = (float)hum_value->valuedouble;
    }
    cJSON_Delete(root);
}
