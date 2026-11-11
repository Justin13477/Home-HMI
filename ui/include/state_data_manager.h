#ifndef STATE_DATA_MANAGER_H
#define STATE_DATA_MANAGER_H

#include "lvgl.h"
#include "datatypes.h"
#include "ui_pages.h"
#include "data_manager.h"

#define UI_INACTIVITY_TIMEOUT 10000

typedef enum {
    PAGE_MAIN,
    PAGE_SETTINGS,
    PAGE_CLIMATE,
    PAGE_LIGHTING
} page_state_t;

extern page_state_t current_page_state;
extern page_state_t next_page_state;

// pages
void page_switcher_set_page_state(page_state_t next);

void load_new_page();

void set_page_home(lv_event_t *e);
void set_page_settings(lv_event_t *e);
void set_page_climate(lv_event_t *e);
void set_page_lighting(lv_event_t *e);

// tasks
void run_task(void *arg);
void refresh_task(void *arg);




#endif