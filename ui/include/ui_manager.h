#ifndef STATE_DATA_MANAGER_H
#define STATE_DATA_MANAGER_H

#include "lvgl.h"
#include "ui_pages.h"
#include "ui_page_switcher.h"
#include "data_manager.h"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"


#define UI_INACTIVITY_TIMEOUT 10000



// pages

void load_new_page();

// tasks
void run_task(void *arg);
void refresh_task(void *arg);




#endif