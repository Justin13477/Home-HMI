#include "state_data_manager.h"
#include "system_init.h"
#include "ui_pages.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"



lv_obj_t* active_page = NULL;
lv_obj_t* old_page = NULL;
page_state_t current_page_state = PAGE_MAIN;
page_state_t next_page_state = PAGE_MAIN;

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

void load_new_page()
{
    if (current_page_state != next_page_state) {
        current_page_state = next_page_state;
        switch (current_page_state) {
            case PAGE_MAIN:
                old_page = active_page;
                active_page = build_page(main_page, build_main_page);
                lv_screen_load(active_page);
                lv_obj_delete(old_page);
                break;
            case PAGE_SETTINGS:
                old_page = active_page;
                active_page = build_page(settings_page, build_settings_page);
                lv_screen_load(active_page);
                lv_obj_delete(old_page);
                break;
        }
        ESP_LOGI("STATE_DATA_MANAGER", "Page switched to: %d", current_page_state);
    }
}
void run(void *arg)
{
    (void)arg;

    system_init();

    ESP_LOGI("STATE_DATA_MANAGER", "System initialized successfully");
    active_page = build_page(main_page, build_main_page);
    lv_screen_load(active_page);
    while (1) {
        load_new_page();
    
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}