#ifndef UI_BUILD_HANDLER_H
#define UI_BUILD_HANDLERS_H

#include "lvgl.h"
#include "data_manager.h"
#include "datatypes.h"

extern lv_obj_t* keyboard;
extern subpage_state_t subpage_climate;

void textarea_focused_cb(lv_event_t *e);
void settings_wifi_ssid_cb(lv_event_t *e);
void settings_wifi_pass_cb(lv_event_t *e);
void settings_mqtt_address_cb(lv_event_t *e);

void climate_spinbox_increment_cb(lv_event_t* e);
void climate_spinbox_decrement_cb(lv_event_t* e);

static ui_page_switcher_cb_t callback;
void set_handler_cb(ui_page_switcher_cb_t cb);
void flashcard_climate_cb(lv_event_t* e);
void flashcard_lighting_cb(lv_event_t* e);

#endif