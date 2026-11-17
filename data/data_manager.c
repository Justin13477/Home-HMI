#include "data_manager.h"

const char* TAG = "DATA_MANAGER";

tag_map_t map = {0};

// runtime data
app_data_t data = {0};
app_data_t data_snapshot = {0};
sensor_data_t sensors = {0};
dtime_t dtime;
settings_t settings = {0};

// network handles
wifi_config_t wifi_config;
esp_mqtt_client_config_t mqtt_cfg;

SemaphoreHandle_t data_mutex;
SemaphoreHandle_t reconnect_sem;

QueueSetHandle_t queue_set;

void init_queues()
{

    data_queue = xQueueCreate(10, sizeof(mqtt_q_message_t));
    weather_queue = xQueueCreate(1, sizeof(weather_data_t *));

    data_mutex = xSemaphoreCreateMutex();
    reconnect_sem = xSemaphoreCreateBinary();

    queue_set = xQueueCreateSet(11);

    xQueueAddToSet(data_queue, queue_set);
    xQueueAddToSet(weather_queue, queue_set);
}
void init_app_data()
{
 
    sensors.sht41_state = SENSOR_STATUS_OFFLINE;
    sensors.veml7700_state = SENSOR_STATUS_OFFLINE;

    data.sensors = &sensors;
    data.dtime = &dtime;
    data.weather_data = NULL;

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
    tag_map_insert(&map, "home/sensor/veml7700/data", sensor_veml770_data_handler);
    tag_map_insert(&map, "home/sensor/veml7700/state", sensor_veml770_state_handler);

    tag_map_insert(&map, "home/sensor/sht41/data", sensor_sht41_data_handler);
    tag_map_insert(&map, "home/sensor/sht41/state", sensor_sht41_state_handler);
}
void init_data()
{
    init_app_data();
    init_app_data_handlers();
    
}

app_data_t* get_data_snapshot()
{
    xSemaphoreTake(data_mutex, portMAX_DELAY);

    update_time();
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


    while(1)
    {

        QueueSetMemberHandle_t active_queue;

        active_queue = xQueueSelectFromSet(
            queue_set,
            portMAX_DELAY
        );

        if(active_queue == data_queue)
        {
            mqtt_q_message_t msg;

            if(xQueueReceive(data_queue, &msg, 0) == pdPASS)
            {
                data_manager_process_message(&msg);
            }
        }

        if(active_queue == weather_queue)
        {
            weather_data_t* weather = NULL;
            if(xQueueReceive(weather_queue, &weather, 0) == pdPASS)
            {
                data.weather_data = weather;
                ESP_LOGI(TAG, "Received weather ptr queue");
            }
            
        }
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

void update_time()
{
    struct tm time_info;

    if (!time_manager_get_time(&time_info))
    {
        return;
    }


    strftime(dtime.time, sizeof(dtime.time), "%I:%M %p", &time_info);
    
    strftime(dtime.date, sizeof(dtime.date), "%a, %b %d", &time_info);
    
}