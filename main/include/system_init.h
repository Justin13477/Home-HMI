#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

#include "esp_err.h"
#include "esp_log.h"
#include "esp_ldo_regulator.h"
#include "esp_timer.h"
#include "lvgl.h"
#include "bsp_extra.h"
#include "bsp_display.h"
#include "bsp_illuminate.h"
#include "bsp_i2c.h"
#include "wifi_manager.h"
#include "mqtt_manager.h"
#include "ui_styles.h"

/*---------------------------------------------------------------
 * Logging macros
 *--------------------------------------------------------------*/
#define INIT_TAG "INIT"


void system_init(void);

#endif
