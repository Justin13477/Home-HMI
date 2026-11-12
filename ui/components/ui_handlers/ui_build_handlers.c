#include "ui_build_handlers.h"

lv_obj_t* keyboard;

lv_obj_t* ui_build_get_keyboard()
{
    if(keyboard == NULL)
        {
            ESP_LOGE("KEYBOARD", "Pointer to keyboard is NULL");
            return NULL;
        }
    return keyboard;
}

void textarea_focused_cb(lv_event_t *e)
{
    lv_obj_t* textarea = lv_event_get_target(e);


    ESP_LOGI("KEYBOARD", "Keyboard: %p", keyboard);
    ESP_LOGI("KEYBOARD", "Target: %p",
    lv_keyboard_get_textarea(keyboard));
    
    lv_keyboard_set_textarea(keyboard, textarea);
}

void settings_wifi_ssid_cb(lv_event_t *e)
{
    
    lv_obj_t *ta = lv_keyboard_get_textarea(keyboard);

    if (ta == NULL) {
        return;
    }

    const char *text = lv_textarea_get_text(ta);
    
    if (text == NULL) {
        
       return;
    }
    ESP_LOGI("CB", "Text: %s", text);
    snprintf(settings.wifi_ssid, sizeof(settings.wifi_ssid), "%s", text);
    xSemaphoreGive(reconnect_sem);
}