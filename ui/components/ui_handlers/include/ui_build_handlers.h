#ifndef UI_BUILD_HANDLER_H
#define UI_BUILD_HANDLERS_H

#include "lvgl.h"
#include "data_manager.h"

extern lv_obj_t* keyboard;

lv_obj_t* ui_build_get_keyboard();

void textarea_focused_cb(lv_event_t *e);
void settings_wifi_ssid_cb(lv_event_t *e);
void settings_wifi_pass_cb(lv_event_t *e);
void settings_mqtt_address_cb(lv_event_t *e);

#endif