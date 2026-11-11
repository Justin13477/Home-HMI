#ifndef UI_BUILD_H
#define UI_BUILD_H

#include "ui_styles.h"
#include "lvgl.h"
#include "state_data_manager.h"
#include "esp_log.h"


/*
Rooms:
  - Bedroom
  - Bathroom
  - Living Room
  - Kitchen
  - 2nd Bedroom
  - Washroom
  - Mudroom


*/
extern app_data_t *ui_build_snapshot;
extern lv_obj_t* keyboard;

typedef lv_obj_t* (*obj_func_t)(lv_obj_t* parent);
typedef void(*button_cb_t)(lv_event_t* e);

void update_snapshot_task(void *arg);

void update_float_label(lv_obj_t* label, float num);

lv_obj_t* create_keyboard(lv_obj_t* parent);
lv_obj_t* get_keyboard();

lv_obj_t* build_nav_sidebar(lv_obj_t *parent); // take a struct pointer to update state changes via cb
lv_obj_t* build_nav_button_base(lv_obj_t* parent, const char* icon, const char* text, lv_event_cb_t cb);
lv_obj_t* build_nav_button_home(lv_obj_t* parent);
lv_obj_t* build_nav_button_settings(lv_obj_t* parent);
lv_obj_t* build_nav_button_lighting(lv_obj_t* parent);
lv_obj_t* build_nav_button_climate(lv_obj_t* parent);



lv_obj_t* build_header_ribbon(lv_obj_t* parent, obj_func_t page_contents_func); // take a state variable
lv_obj_t* build_header_ribbon_contents(lv_obj_t* parent, lv_obj_t* page_contents); // take a state variable 
lv_obj_t* build_header_ribbon_page_base(lv_obj_t* parent, const char* icon, const char* label, const char* dsc);
lv_obj_t* build_header_ribbon_page_home(lv_obj_t* parent);
lv_obj_t* build_header_ribbon_page_settings(lv_obj_t* parent);
lv_obj_t* build_header_ribbon_page_climate(lv_obj_t* parent);
lv_obj_t* build_header_ribbon_page_lighting(lv_obj_t* parent);

lv_obj_t* build_header_ribbon_timestamp(lv_obj_t* parent); // take a time and date struct

lv_obj_t* build_flashcard_base(lv_obj_t* parent, const char* icon, const char* label, obj_func_t content_func); // take a pointer to state struct
lv_obj_t* build_flashcard_content_base1(lv_obj_t* parent, const char* label1, float num);

lv_obj_t* build_flashcard_temp(lv_obj_t* parent);
lv_obj_t* build_flashcard_temp_content(lv_obj_t* parent); // take a small struct of temp readings

lv_obj_t* build_flashcard_hum(lv_obj_t* parent); // small struct for lumen readings
lv_obj_t* build_flashcard_hum_content(lv_obj_t* parent); // small

lv_obj_t* build_flashcard_lumen(lv_obj_t* parent); // small struct for lumen readings
lv_obj_t* build_flashcard_lumen_content(lv_obj_t* parent); // small

lv_obj_t* build_settings_network_options(lv_obj_t* parent);

lv_obj_t* build_settings_section(lv_obj_t* parent, const char* header);
lv_obj_t* build_settings_entry(lv_obj_t* parent, const char* label, const char* placeholder, button_cb_t cb);


static void textarea_focused_cb(lv_event_t *e);
static void settings_wifi_ssid_cb(lv_event_t *e);
static void settings_wifi_pass_cb(lv_event_t *e);
static void settings_mqtt_address_cb(lv_event_t *e);

#endif

