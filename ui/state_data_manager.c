#include "state_data_manager.h"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "tag_map.h"




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
void set_page_climate(lv_event_t *e)
{
    (void)e;
    page_switcher_set_page_state(PAGE_CLIMATE);
    ESP_LOGI("STATE_DATA_MANAGER", "Switching to Climate page");
}

void set_page_lighting(lv_event_t *e)
{
    (void)e;
    page_switcher_set_page_state(PAGE_LIGHTING);
    ESP_LOGI("STATE_DATA_MANAGER", "Switching to Lighting page");
}

void load_new_page()
{
    ui_build_snapshot = get_data_snapshot();
    if (current_page_state != next_page_state) {
        current_page_state = next_page_state;
        lv_obj_delete(get_keyboard());
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
            case PAGE_CLIMATE:
                old_page = active_page;
                active_page = build_page(climate_page, build_climate_page);
                lv_screen_load(active_page);
                lv_obj_delete(old_page);
                break;
            case PAGE_LIGHTING:
                old_page = active_page;
                active_page = build_page(lighting_page, build_lighting_page);
                lv_screen_load(active_page);
                lv_obj_delete(old_page);
                break;
        }
        ESP_LOGI("STATE_DATA_MANAGER", "Page switched to: %d", current_page_state);
    }

    uint32_t inactive_time = lv_display_get_inactive_time(NULL);

    if(inactive_time > UI_INACTIVITY_TIMEOUT)
    {
        if(current_page_state != next_page_state)
            lv_obj_delete(get_keyboard());
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
            case PAGE_CLIMATE:
                old_page = active_page;
                active_page = build_page(climate_page, build_climate_page);
                lv_screen_load(active_page);
                lv_obj_delete(old_page);
                break;
            case PAGE_LIGHTING:
                old_page = active_page;
                active_page = build_page(lighting_page, build_lighting_page);
                lv_screen_load(active_page);
                lv_obj_delete(old_page);
                break;
        }
        lv_display_trigger_activity(NULL);
    }
}


void run_task(void *arg)
{
    (void)arg;

    
    init_data();

    ESP_LOGI("STATE_DATA_MANAGER", "System initialized successfully");

    ui_build_snapshot = get_data_snapshot();
    active_page = build_page(main_page, build_main_page);
    lv_screen_load(active_page);
    while (1) {
        
        load_new_page();

        vTaskDelay(pdMS_TO_TICKS(100));

        
    }
}


void refresh_task(void *arg)
{
    while(1)
    {
        old_page = active_page;
        active_page = build_page(main_page, build_main_page);
        lv_screen_load(active_page);
        lv_obj_delete(old_page);

        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}

