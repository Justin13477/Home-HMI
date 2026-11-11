#include "mqtt_manager.h"

#include "esp_log.h"

static const char *TAG = "MQTT";

static esp_mqtt_client_handle_t mqtt_client = NULL;
static bool mqtt_connected = false;
QueueHandle_t data_queue;

static const char* broker_address;

esp_mqtt_client_handle_t get_client()
{
    return mqtt_client;
}

static void mqtt_event_handler(
    void *handler_args,
    esp_event_base_t base,
    int32_t event_id,
    void *event_data
);

esp_err_t mqtt_manager_init(const char* _broker_address)
{
    broker_address = _broker_address;
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = broker_address,
    };

    mqtt_client = esp_mqtt_client_init(&mqtt_cfg);

    if (mqtt_client == NULL)
    {
        ESP_LOGE(TAG, "Failed to initialize MQTT client");
        return ESP_FAIL;
    }

    esp_mqtt_client_register_event(
        mqtt_client,
        ESP_EVENT_ANY_ID,
        mqtt_event_handler,
        NULL
    );

    data_queue = xQueueCreate(10, sizeof(mqtt_q_message_t));

    return ESP_OK;
}

static void mqtt_event_handler(
    void *handler_args,
    esp_event_base_t base,
    int32_t event_id,
    void *event_data
)
{
    esp_mqtt_event_handle_t event = event_data;

    switch (event_id)
    {
        case MQTT_EVENT_CONNECTED:

            ESP_LOGI(TAG, "Connected to broker");

            mqtt_connected = true;

            esp_mqtt_client_subscribe(
                mqtt_client,
                "home/bedroom/sensor/sht41/data",
                1
            );

            esp_mqtt_client_subscribe(
                mqtt_client,
                "home/bedroom/sensor/veml7700/data",
                1
            );

            break;


        case MQTT_EVENT_DISCONNECTED:

            ESP_LOGW(TAG, "Disconnected from broker");

            mqtt_connected = false;

            break;


        case MQTT_EVENT_DATA:

            ESP_LOGI(TAG, "Incoming MQTT message");
            mqtt_q_message_t msg;
            msg.topic = event->topic;
            msg.payload = event->data;
            msg.payload_len = event->data_len;

            xQueueSend(data_queue, &msg, portMAX_DELAY);

            ESP_LOGI(
                TAG,
                "Topic: %.*s",
                event->topic_len,
                event->topic
            );

            ESP_LOGI(
                TAG,
                "Payload: %.*s",
                event->data_len,
                event->data
            );

            break;


        case MQTT_EVENT_ERROR:

            ESP_LOGE(TAG, "MQTT communication error");

            break;


        default:
            break;
    }
}

esp_err_t mqtt_manager_publish(
    const char *topic,
    const char *payload,
    int qos
)
{
    if (!mqtt_connected)
    {
        ESP_LOGW(TAG, "MQTT disconnected");
        return ESP_ERR_INVALID_STATE;
    }

    int msg_id = esp_mqtt_client_publish(
        mqtt_client,
        topic,
        payload,
        0,
        qos,
        0
    );

    if (msg_id < 0)
    {
        ESP_LOGE(TAG, "Failed to publish message");
        return ESP_FAIL;
    }

    return ESP_OK;
}

esp_err_t mqtt_manager_start(void)
{
    if (mqtt_client == NULL)
    {
        return ESP_ERR_INVALID_STATE;
    }

    return esp_mqtt_client_start(mqtt_client);
}

bool mqtt_manager_is_connected(void)
{
    return mqtt_connected;
}

const char* get_broker_address()
{
    return broker_address;
}