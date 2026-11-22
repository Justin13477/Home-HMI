#ifndef UI_PAGE_SWITCHER_H
#define UI_PAGE_SWITCHER_H

#include "lvgl.h"
#include "esp_log.h"
#include "datatypes.h"


extern page_state_t current_page_state;
extern page_state_t next_page_state;

extern subpage_state_t current_subpage_climate;
extern subpage_state_t next_subpage_climate;

void page_switcher_set_page_state(page_state_t next);

void set_page_home(lv_event_t *e);
void set_page_settings(lv_event_t *e);
void set_page_climate(lv_event_t *e);
void set_page_lighting(lv_event_t *e);
void set_page_weather(lv_event_t *e);

#endif