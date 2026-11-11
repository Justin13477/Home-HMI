#ifndef STATE_DATA_MANAGER_H
#define STATE_DATA_MANAGER_H

#include "lvgl.h"
#include "datatypes.h"
#include "mqtt_manager.h"
#include "cJSON.h"
#include "ui_pages.h"
#include "esp_wifi.h"

#define UI_INACTIVITY_TIMEOUT 10000

typedef enum {
    PAGE_MAIN,
    PAGE_SETTINGS,
    PAGE_CLIMATE,
    PAGE_LIGHTING
} page_state_t;

extern page_state_t current_page_state;
extern page_state_t next_page_state;

extern wifi_config_t wifi_config;
extern esp_mqtt_client_config_t mqtt_cfg; 

extern settings_t settings;

extern SemaphoreHandle_t reconnect_sem;

// data
void init_data();
void init_app_data();
void init_network_data();
void init_app_data_handlers();

app_data_t* get_data_snapshot();

// pages
void page_switcher_set_page_state(page_state_t next);

void load_new_page();

void set_page_home(lv_event_t *e);
void set_page_settings(lv_event_t *e);
void set_page_climate(lv_event_t *e);
void set_page_lighting(lv_event_t *e);

// tasks
void run_task(void *arg);
void data_task(void *arg);
void refresh_task(void *arg);
void network_task(void *arg);

void data_manager_process_message(mqtt_q_message_t *msg);


// TODO: 
// Integrate all handlers for topic tree
// Add logs 
// handlers
void bedroom_sensor_veml770_data_handler(app_data_t *data, const char* payload, uint32_t length);
void bedroom_sensor_veml770_state_handler(app_data_t *data, const char* payload, uint32_t length);

void bedroom_sensor_sht41_data_handler(app_data_t *data, const char* payload, uint32_t length);
void bedroom_sensor_sht41_state_handler(app_data_t *data, const char* payload, uint32_t length);



#endif