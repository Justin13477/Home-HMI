#ifndef STATE_DATA_MANAGER_H
#define STATE_DATA_MANAGER_H

#include "lvgl.h"

typedef enum {
    PAGE_MAIN,
    PAGE_SETTINGS,
} page_state_t;

extern page_state_t current_page_state;
extern page_state_t next_page_state;

void page_switcher_set_page_state(page_state_t next);

void load_new_page();

void set_page_home(lv_event_t *e);
void set_page_settings(lv_event_t *e);

void run(void *arg);

#endif