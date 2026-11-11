#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <string.h>

#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "nvs_flash.h"
#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

void wifi_init_sta(void);

#endif
