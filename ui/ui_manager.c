#include "ui_manager.h"

lv_obj_t* active_page = NULL;
lv_obj_t* old_page = NULL;




void load_new_page()
{
    ui_build_snapshot = get_data_snapshot();
    if (current_page_state != next_page_state) {
        current_page_state = next_page_state;
        lv_obj_delete(ui_build_get_keyboard());
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
            lv_obj_delete(ui_build_get_keyboard());
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

