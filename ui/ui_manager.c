#include "ui_manager.h"
#include "esp_lvgl_port.h"

lv_obj_t* active_page = NULL;
lv_obj_t* old_page = NULL;

static const char *TAG = "UI_MANAGER";

void load_new_page()
{
    ui_build_snapshot = get_data_snapshot();
    if (!lvgl_port_lock(0)) {
        ESP_LOGE(TAG, "Failed to lock LVGL for page update");
        return;
    }

    bool page_rebuilt = false;
    if (current_page_state != next_page_state || current_subpage_climate != next_subpage_climate) {
        current_page_state = next_page_state;
        current_subpage_climate = next_subpage_climate;
        old_page = active_page;
        if(old_page != NULL)
        {
            lv_obj_clean(old_page);
        }
        keyboard = NULL;
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
        ESP_LOGI(TAG, "Page switched to: %d", current_page_state);
        page_rebuilt = true;
    }

    uint32_t inactive_time = lv_display_get_inactive_time(NULL);

    if(!page_rebuilt && inactive_time > UI_INACTIVITY_TIMEOUT)
    {
        old_page = active_page;
        if(old_page != NULL)
        {
            lv_obj_clean(old_page);
        }
        keyboard = NULL;
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

    lvgl_port_unlock();
}


void run_task(void *arg)
{
    (void)arg;

    
    
    init_handlers(page_switcher_set_page_state);

    ESP_LOGI(TAG, "System initialized successfully");

    ui_build_snapshot = get_data_snapshot();
    if (!lvgl_port_lock(0)) {
        ESP_LOGE(TAG, "Failed to lock LVGL during initial page creation");
        vTaskDelete(NULL);
        return;
    }

    active_page = build_page(main_page, build_main_page);
    lv_screen_load(active_page);
    lvgl_port_unlock();

    while (1) {
        
        load_new_page();

        vTaskDelay(pdMS_TO_TICKS(100));

        
    }
}


void refresh_task(void *arg)
{
    while(1)
    {
        if (!lvgl_port_lock(0)) {
            ESP_LOGE(TAG, "Failed to lock LVGL for page refresh");
        } else {
            old_page = active_page;
            if(old_page != NULL)
            {
                lv_obj_clean(old_page);
            }
            keyboard = NULL;
            active_page = build_page(main_page, build_main_page);
            lv_screen_load(active_page);
            lv_obj_delete(old_page);
            lvgl_port_unlock();
        }

        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}

