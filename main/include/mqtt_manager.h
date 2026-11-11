#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include "esp_err.h"
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "datatypes.h"
#include "mqtt_client.h"

extern QueueHandle_t data_queue;

esp_err_t mqtt_manager_init(const char* _broker_address);

esp_err_t mqtt_manager_start(void);

esp_err_t mqtt_manager_publish(const char *topic, const char *payload, int qos);

bool mqtt_manager_is_connected(void);

const char* get_broker_address();

esp_mqtt_client_handle_t get_client();
#endif