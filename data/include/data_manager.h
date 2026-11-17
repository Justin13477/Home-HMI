#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "data_handlers.h"
#include "mqtt_manager.h"
#include "wifi_manager.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "tag_map.h"
#include "time_manager.h"
#include "weather_manager.h"

extern settings_t settings;                           
extern SemaphoreHandle_t reconnect_sem;

void init_queues();
void init_network_data();
void init_data(); // System Init

app_data_t* get_data_snapshot(); // Getting App Data Snapshot
void update_time();


void data_task(void *arg); // For handling incoming data
void network_task(void *arg); // For handling network events like reconnect

#endif