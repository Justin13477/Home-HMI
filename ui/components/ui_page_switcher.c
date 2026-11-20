#include "ui_page_switcher.h"

page_state_t current_page_state = PAGE_MAIN;
page_state_t next_page_state = PAGE_MAIN;
subpage_state_t subpage_climate = SUBPAGE_CLIMATE;

void page_switcher_set_page_state(page_state_t next)
{
    next_page_state = next;
}

void set_page_home(lv_event_t *e)
{
    (void)e;
    page_switcher_set_page_state(PAGE_MAIN);
    ESP_LOGI("STATE_DATA_MANAGER", "Switching to Home page");
}

void set_page_settings(lv_event_t *e)
{
    (void)e;
    page_switcher_set_page_state(PAGE_SETTINGS);
    ESP_LOGI("STATE_DATA_MANAGER", "Switching to Settings page");
}
void set_page_climate(lv_event_t *e)
{
    (void)e;
    subpage_climate = SUBPAGE_CLIMATE;
    page_switcher_set_page_state(PAGE_CLIMATE);
    ESP_LOGI("STATE_DATA_MANAGER", "Switching to Climate page");
}
void set_page_weather(lv_event_t *e)
{
    (void)e;
    subpage_climate = SUBPAGE_WEATHER;
    page_switcher_set_page_state(PAGE_CLIMATE);
    ESP_LOGI("STATE_DATA_MANAGER", "Switching to Weather page");
}

void set_page_lighting(lv_event_t *e)
{
    (void)e;
    page_switcher_set_page_state(PAGE_LIGHTING);
    ESP_LOGI("STATE_DATA_MANAGER", "Switching to Lighting page");
}