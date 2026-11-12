#include "data_manager.h"

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


    snprintf(settings.mqtt_address, sizeof(settings.mqtt_address), "%s", mqtt_manager_get_broker_address());
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

            ESP_ERROR_CHECK(esp_mqtt_client_disconnect(mqtt_manager_get_client()));
            ESP_ERROR_CHECK(esp_mqtt_client_set_uri(mqtt_manager_get_client(), settings.mqtt_address));

            ESP_ERROR_CHECK(esp_mqtt_client_reconnect(mqtt_manager_get_client()));
        }
    }
}


