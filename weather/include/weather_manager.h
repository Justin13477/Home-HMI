#ifndef WEATHER_MANAGER_H
#define WEATHER_MANAGER_H

#include "cJSON.h"
#include "wifi_manager.h"
#include "datatypes.h"




// https://open-meteo.com/

void weather_manager_init();

bool weather_manager_get_data(weather_data_t* data);

#endif