#ifndef UI_PAGE_SWITCHER_H
#define UI_PAGE_SWITCHER_H

#include "lvgl.h"
#include "esp_log.h"

typedef enum {
    PAGE_MAIN,
    PAGE_SETTINGS,
    PAGE_CLIMATE,
    PAGE_LIGHTING
} page_state_t;

extern page_state_t current_page_state;
extern page_state_t next_page_state;

void page_switcher_set_page_state(page_state_t next);

void set_page_home(lv_event_t *e);
void set_page_settings(lv_event_t *e);
void set_page_climate(lv_event_t *e);
void set_page_lighting(lv_event_t *e);

#endif