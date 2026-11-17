#ifndef WEATHER_MANAGER_H
#define WEATHER_MANAGER_H

#include "cJSON.h"
#include "wifi_manager.h"
#include "datatypes.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"


extern QueueHandle_t weather_queue;

// https://open-meteo.com/

void weather_manager_init();

void weather_manager_task(void *args);

#endif