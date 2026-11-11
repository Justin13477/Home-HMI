#include "ui_build.h"

app_data_t *ui_build_snapshot;
lv_obj_t* keyboard;

void update_snapshot_task(void *arg)
{
    while(1)
    {
        ui_build_snapshot = get_data_snapshot();
        if(ui_build_snapshot == NULL)
            ESP_LOGI("get_data_snapshot", "Snapshot returned null pointer");
        
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void update_float_label(lv_obj_t* label, float num)
{
    char buffer[32];
    float_to_char(num, buffer, sizeof(buffer)); // prep

    lv_label_set_text(label, buffer);
}

lv_obj_t* create_keyboard(lv_obj_t* parent)
{
    lv_obj_t* keyboard = lv_keyboard_create(parent);
    lv_obj_set_size(keyboard, lv_pct(80), lv_pct(40));
    //lv_obj_add_flag(keyboard, LV_OBJ_FLAG_IGNORE_LAYOUT);
    apply_main_style(keyboard);
    

    return keyboard;
}

lv_obj_t* get_keyboard()
{
    return keyboard;
}

static void textarea_focused_cb(lv_event_t *e)
{
    lv_obj_t* textarea = lv_event_get_target(e);


    ESP_LOGI("KEYBOARD", "Keyboard: %p", keyboard);
    ESP_LOGI("KEYBOARD", "Target: %p",
    lv_keyboard_get_textarea(keyboard));
    
    lv_keyboard_set_textarea(keyboard, textarea);
}

lv_obj_t* build_nav_sidebar(lv_obj_t* parent)
{

    lv_obj_t* sidebar = lv_obj_create(parent);
        apply_main_style(sidebar);
        lv_obj_set_size(sidebar, lv_pct(15), lv_pct(100));
        lv_obj_set_style_margin_all(sidebar, 0, LV_PART_MAIN);
        lv_obj_set_flex_flow(sidebar, LV_FLEX_FLOW_COLUMN);

    return sidebar;
}

lv_obj_t* build_nav_button_base(lv_obj_t* parent, const char* icon, const char* text, lv_event_cb_t cb)
{
    lv_obj_t* button = lv_button_create(parent);
    apply_nav_button_style(button);
    lv_obj_set_style_size(button, lv_pct(100), lv_pct(19), LV_STATE_DEFAULT);
    lv_obj_add_event_cb(button, cb, LV_EVENT_CLICKED, NULL);

        lv_obj_t* icon_label = lv_label_create(button);
        apply_nav_button_icon_label_style(icon_label);
        lv_label_set_text(icon_label, icon);
        

        lv_obj_t* text_label = lv_label_create(button);
        apply_nav_button_prim_label_style(text_label);
        lv_label_set_text(text_label, text);
    return button;
}

lv_obj_t* build_nav_button_home(lv_obj_t* parent)
{
    return build_nav_button_base(parent, LV_SYMBOL_HOME, "Home", set_page_home);
}

lv_obj_t* build_nav_button_settings(lv_obj_t* parent)
{
    return build_nav_button_base(parent, LV_SYMBOL_SETTINGS, "Settings", set_page_settings);
}
lv_obj_t* build_nav_button_lighting(lv_obj_t* parent)
{
    return build_nav_button_base(parent, LV_SYMBOL_POWER, "Lighting", set_page_lighting);
}

lv_obj_t* build_nav_button_climate(lv_obj_t* parent)
{
    return build_nav_button_base(parent, LV_SYMBOL_BELL, "Climate", set_page_climate);
}



lv_obj_t* build_header_ribbon_page_base(lv_obj_t* parent, const char* icon, const char* label, const char* dsc)
{
    lv_obj_t* page_contents = lv_obj_create(parent);
    apply_main_style(page_contents);
    lv_obj_set_style_border_opa(page_contents, LV_OPA_0, 0);
    lv_obj_set_flex_flow(page_contents, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(page_contents, 
                        LV_FLEX_ALIGN_START, 
                        LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER);

        lv_obj_t* page_contents_icon_label = lv_label_create(page_contents);
        lv_label_set_text(page_contents_icon_label, icon); 
        lv_obj_set_size(page_contents, lv_pct(20), lv_pct(100));
        lv_obj_center(page_contents_icon_label);
        
        
        apply_nav_button_icon_label_style(page_contents_icon_label);
        
        

        lv_obj_t* page_dsc = lv_obj_create(page_contents);
        apply_main_style(page_dsc);
        lv_obj_set_style_border_opa(page_dsc, LV_OPA_0, 0);
        lv_obj_set_flex_flow(page_dsc, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_size(page_dsc, lv_pct(49), lv_pct(100));

            lv_obj_t* page_label = lv_label_create(page_dsc);
            lv_label_set_text(page_label, label);
            apply_header_big_label_style(page_label);

    

            lv_obj_t* dsc_label = lv_label_create(page_dsc);
            lv_label_set_text(dsc_label, dsc);
            apply_header_sm_label_style(dsc_label);

    return page_contents;
    
}
lv_obj_t* build_header_ribbon_page_home(lv_obj_t* parent)
{
    return build_header_ribbon_page_base(parent, LV_SYMBOL_HOME, "Home", "Overview");
}
lv_obj_t* build_header_ribbon_page_settings(lv_obj_t* parent)
{
    return build_header_ribbon_page_base(parent, LV_SYMBOL_SETTINGS, "Settings", "Mixin Shit Up");
}

lv_obj_t* build_header_ribbon_page_climate(lv_obj_t* parent)
{
    return build_header_ribbon_page_base(parent, LV_SYMBOL_BELL, "Climate", "Air Shenanigans");
}

lv_obj_t* build_header_ribbon_page_lighting(lv_obj_t* parent)
{
    return build_header_ribbon_page_base(parent, LV_SYMBOL_POWER, "Lighting", "Disco Mode");
}


lv_obj_t* build_header_ribbon(lv_obj_t* parent, obj_func_t page_contents_func)
{
    lv_obj_t *ribbon = lv_obj_create(parent);
        apply_main_style(ribbon);
        lv_obj_set_size(ribbon, lv_pct(100), lv_pct(20));
        lv_obj_set_style_margin_all(ribbon, 0, LV_PART_MAIN);
        lv_obj_set_flex_flow(ribbon, LV_FLEX_FLOW_ROW);

        lv_obj_t* page_contents = page_contents_func(ribbon);
        lv_obj_set_size(page_contents, lv_pct(49), lv_pct(100));

        lv_obj_t* ribbon_timestamp = build_header_ribbon_timestamp(ribbon);
        lv_obj_set_size(ribbon_timestamp, lv_pct(49), lv_pct(100));
    return ribbon;

}

lv_obj_t* build_header_ribbon_timestamp(lv_obj_t* parent)
{
    lv_obj_t* ribbon_timestamp = lv_obj_create(parent);
    apply_main_style(ribbon_timestamp);
    lv_obj_set_style_border_opa(ribbon_timestamp, 0, 0);
    lv_obj_set_flex_flow(ribbon_timestamp, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ribbon_timestamp,
                        LV_FLEX_ALIGN_START, 
                        LV_FLEX_ALIGN_CENTER, 
                        LV_FLEX_ALIGN_END);

        
        
        lv_obj_t* ribbon_timestamp_label_date = lv_label_create(ribbon_timestamp);
        apply_header_sm_label_style(ribbon_timestamp_label_date);
        lv_label_set_text(ribbon_timestamp_label_date, "Date Here");

        lv_obj_t* ribbon_timestamp_label_time = lv_label_create(ribbon_timestamp);
        apply_header_sm_label_style(ribbon_timestamp_label_time);
        lv_label_set_text(ribbon_timestamp_label_time, "Time Here");
    return ribbon_timestamp;
}



lv_obj_t* build_flashcard_base(lv_obj_t* parent, const char* icon, const char* label, obj_func_t content_func)                           
{
    lv_obj_t* flashcard = lv_obj_create(parent);
    lv_obj_set_size(flashcard, lv_pct(49), lv_pct(48));
    apply_flashcard_style(flashcard);
    lv_obj_set_flex_flow(flashcard, LV_FLEX_FLOW_COLUMN);

        lv_obj_t* flashcard_header = lv_button_create(flashcard);
        lv_obj_set_size(flashcard_header, lv_pct(100), lv_pct(29));
        apply_flashcard_button_style(flashcard_header);
        lv_obj_set_flex_align(flashcard_header, 
                            LV_FLEX_ALIGN_SPACE_BETWEEN,
                            LV_FLEX_ALIGN_CENTER,
                            LV_FLEX_ALIGN_CENTER);

            lv_obj_t* flashcard_header_icon = lv_label_create(flashcard_header);
            lv_label_set_text(flashcard_header_icon, icon);
            apply_nav_button_icon_label_style(flashcard_header_icon);

            lv_obj_t* flashcard_header_label = lv_label_create(flashcard_header);
            lv_label_set_text(flashcard_header_label, label);

            lv_obj_t* flashcard_header_director_icon = lv_label_create(flashcard_header);
            lv_label_set_text(flashcard_header_director_icon, LV_SYMBOL_PLUS);


        lv_obj_t* flashcard_content = content_func(flashcard);

    return flashcard;
}

lv_obj_t* build_flashcard_content_base1(lv_obj_t* parent, const char* label1, float num)
{
    
    lv_obj_t* flashcard_content = lv_obj_create(parent);
    apply_main_style(flashcard_content);
    lv_obj_remove_flag(flashcard_content, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_left(flashcard_content, 20, 0);
    lv_obj_set_style_pad_right(flashcard_content, 20, 0);
    lv_obj_set_flex_flow(flashcard_content, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(flashcard_content, 
                        LV_FLEX_ALIGN_SPACE_BETWEEN, 
                        LV_FLEX_ALIGN_CENTER, 
                        LV_FLEX_ALIGN_CENTER);

        lv_obj_t* flashcard_content_label1 = lv_label_create(flashcard_content);
        apply_header_sm_label_style(flashcard_content_label1);
        
        lv_label_set_text(flashcard_content_label1, label1);

        lv_obj_t* flashcard_content_label2 = lv_label_create(flashcard_content);
        lv_obj_set_style_text_color(flashcard_content_label2, lv_color_hex(COLOR_PRIM_AC), 0);
        apply_header_sm_label_style(flashcard_content_label2);
        update_float_label(flashcard_content_label2, num);


    return flashcard_content;
}

lv_obj_t* build_flashcard_temp_content(lv_obj_t* parent)
{
    

    lv_obj_t* flashcard_temp_content = lv_obj_create(parent);
    apply_main_style(flashcard_temp_content);
    lv_obj_set_size(flashcard_temp_content, lv_pct(100), lv_pct(65));
    lv_obj_set_flex_flow(flashcard_temp_content, LV_FLEX_FLOW_COLUMN);  
    lv_obj_set_style_border_opa(flashcard_temp_content, LV_OPA_0, 0);

    /*
Rooms:
  - Bedroom
  - Bathroom
  - Living Room
  - Kitchen
  - 2nd Bedroom
  - Washroom
  - Mudroom
*/

        lv_obj_t* flashcard_temp_content_bedroom = build_flashcard_content_base1(flashcard_temp_content, "Bedroom", ui_build_snapshot->bedroom->temp);
        lv_obj_set_size(flashcard_temp_content_bedroom, lv_pct(100), lv_pct(30));


        lv_obj_t* flashcard_temp_content_bathroom = build_flashcard_content_base1(flashcard_temp_content, "Bathroom", 0);
        lv_obj_set_size(flashcard_temp_content_bathroom, lv_pct(100), lv_pct(30));

        lv_obj_t* flashcard_temp_content_living_room = build_flashcard_content_base1(flashcard_temp_content, "Living Room", 0);
        lv_obj_set_size(flashcard_temp_content_living_room, lv_pct(100), lv_pct(30));

        lv_obj_t* flashcard_temp_content_kitchen = build_flashcard_content_base1(flashcard_temp_content, "Kitchen", 0);
        lv_obj_set_size(flashcard_temp_content_kitchen, lv_pct(100), lv_pct(30));

        lv_obj_t* flashcard_temp_content_2nd_bedroom = build_flashcard_content_base1(flashcard_temp_content, "2nd Bedroom", 0);
        lv_obj_set_size(flashcard_temp_content_2nd_bedroom, lv_pct(100), lv_pct(30));

        lv_obj_t* flashcard_temp_content_washroom = build_flashcard_content_base1(flashcard_temp_content, "Washroom", 0);
        lv_obj_set_size(flashcard_temp_content_washroom, lv_pct(100), lv_pct(30));



    return flashcard_temp_content;
}

lv_obj_t* build_flashcard_temp(lv_obj_t* parent)
{
    return build_flashcard_base(parent, LV_SYMBOL_WARNING, "Temperature", build_flashcard_temp_content);
}


lv_obj_t* build_flashcard_hum_content(lv_obj_t* parent)
{
    lv_obj_t* flashcard_hum_content = lv_obj_create(parent);
    apply_main_style(flashcard_hum_content);
    lv_obj_set_size(flashcard_hum_content, lv_pct(100), lv_pct(65));
    lv_obj_set_flex_flow(flashcard_hum_content, LV_FLEX_FLOW_COLUMN);  
    lv_obj_set_style_border_opa(flashcard_hum_content, LV_OPA_0, 0);

    /*
Rooms:
  - Bedroom
  - Bathroom
  - Living Room
  - Kitchen
  - 2nd Bedroom
  - Washroom
  - Mudroom
*/

        lv_obj_t* flashcard_hum_content_bedroom = build_flashcard_content_base1(flashcard_hum_content, "Bedroom", ui_build_snapshot->bedroom->hum);
        lv_obj_set_size(flashcard_hum_content_bedroom, lv_pct(100), lv_pct(30));


        lv_obj_t* flashcard_hum_content_bathroom = build_flashcard_content_base1(flashcard_hum_content, "Bathroom", 0);
        lv_obj_set_size(flashcard_hum_content_bathroom, lv_pct(100), lv_pct(30));

        lv_obj_t* flashcard_hum_content_living_room = build_flashcard_content_base1(flashcard_hum_content, "Living Room", 0);
        lv_obj_set_size(flashcard_hum_content_living_room, lv_pct(100), lv_pct(30));

        lv_obj_t* flashcard_hum_content_kitchen = build_flashcard_content_base1(flashcard_hum_content, "Kitchen", 0);
        lv_obj_set_size(flashcard_hum_content_kitchen, lv_pct(100), lv_pct(30));

        lv_obj_t* flashcard_hum_content_2nd_bedroom = build_flashcard_content_base1(flashcard_hum_content, "2nd Bedroom", 0);
        lv_obj_set_size(flashcard_hum_content_2nd_bedroom, lv_pct(100), lv_pct(30));

        lv_obj_t* flashcard_hum_content_washroom = build_flashcard_content_base1(flashcard_hum_content, "Washroom", 0);
        lv_obj_set_size(flashcard_hum_content_washroom, lv_pct(100), lv_pct(30));


    return flashcard_hum_content;
}

lv_obj_t* build_flashcard_hum(lv_obj_t* parent)
{
    return build_flashcard_base(parent, LV_SYMBOL_LOOP, "Humidity", build_flashcard_hum_content);
}

lv_obj_t* build_flashcard_lumen_content(lv_obj_t* parent)
{
    
    lv_obj_t* flashcard_lumen_content = lv_obj_create(parent);
    apply_main_style(flashcard_lumen_content);
    lv_obj_set_size(flashcard_lumen_content, lv_pct(100), lv_pct(65));
    lv_obj_set_flex_flow(flashcard_lumen_content, LV_FLEX_FLOW_COLUMN);  
    lv_obj_set_style_border_opa(flashcard_lumen_content, LV_OPA_0, 0);

        lv_obj_t* flashcard_lumen_content_bedroom = build_flashcard_content_base1(flashcard_lumen_content, "Bedroom", ui_build_snapshot->bedroom->lux);
        lv_obj_set_size(flashcard_lumen_content_bedroom, lv_pct(100), lv_pct(30));

        lv_obj_t* flashcard_lumen_content_bathroom = build_flashcard_content_base1(flashcard_lumen_content, "Bathroom", 0);
        lv_obj_set_size(flashcard_lumen_content_bathroom, lv_pct(100), lv_pct(30));

        lv_obj_t* flashcard_lumen_content_living_room = build_flashcard_content_base1(flashcard_lumen_content, "Living Room", 0);
        lv_obj_set_size(flashcard_lumen_content_living_room, lv_pct(100), lv_pct(30));

        lv_obj_t* flashcard_lumen_content_kitchen = build_flashcard_content_base1(flashcard_lumen_content, "Kitchen", 0);
        lv_obj_set_size(flashcard_lumen_content_kitchen, lv_pct(100), lv_pct(30));

        lv_obj_t* flashcard_lumen_content_2nd_bedroom = build_flashcard_content_base1(flashcard_lumen_content, "2nd Bedroom", 0);
        lv_obj_set_size(flashcard_lumen_content_2nd_bedroom, lv_pct(100), lv_pct(30));

        lv_obj_t* flashcard_lumen_content_washroom = build_flashcard_content_base1(flashcard_lumen_content, "Washroom", 0);
        lv_obj_set_size(flashcard_lumen_content_washroom, lv_pct(100), lv_pct(30));


    return flashcard_lumen_content;
}

lv_obj_t* build_flashcard_lumen(lv_obj_t* parent)
{
    return build_flashcard_base(parent, LV_SYMBOL_EYE_OPEN, "Lumen", build_flashcard_lumen_content);
}

lv_obj_t* build_settings_section(lv_obj_t* parent, const char* header)
{

    lv_obj_t* settings_section = lv_obj_create(parent);
    lv_obj_set_flex_flow(settings_section, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_bg_opa(settings_section, 0, 0);
    lv_obj_set_style_border_opa(settings_section, 0, 0);
    lv_obj_set_size(settings_section, lv_pct(100), lv_pct(100));

        lv_obj_t* section_header = lv_label_create(settings_section);
            apply_header_big_label_style(section_header);
            lv_label_set_text(section_header, header);

    return settings_section;
}
lv_obj_t* build_settings_entry(lv_obj_t* parent, const char* label, const char* placeholder, button_cb_t cb)
{
    lv_obj_t* setting_entry = lv_obj_create(parent);
    lv_obj_set_flex_flow(setting_entry, LV_FLEX_FLOW_ROW);
    apply_main_style(setting_entry);
    lv_obj_set_size(setting_entry, lv_pct(100), lv_pct(40));
    lv_obj_set_style_border_opa(setting_entry, 0, 0);

        lv_obj_t* setting_label = lv_label_create(setting_entry);
        apply_header_sm_label_style(setting_label);
        lv_label_set_text(setting_label, label);
        lv_obj_set_style_border_opa(setting_label, 0, 0);

        lv_obj_t* setting_textarea = lv_textarea_create(setting_entry);
        apply_textarea_style(setting_textarea);
        lv_textarea_set_one_line(setting_textarea, true);
        lv_textarea_set_placeholder_text(setting_textarea, placeholder);
        lv_obj_add_flag(setting_textarea, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_ADV_HITTEST);
        lv_obj_add_event_cb(setting_textarea, textarea_focused_cb, LV_EVENT_FOCUSED, NULL);

        lv_obj_t* setting_button = lv_button_create(setting_entry);
        apply_flashcard_button_style(setting_button);
        lv_obj_add_event_cb(setting_button, cb, LV_EVENT_ALL, NULL);
        lv_obj_set_size(setting_button, lv_pct(10), lv_pct(100));
            lv_obj_t* setting_button_label = lv_label_create(setting_button);
            apply_header_sm_label_style(setting_button_label);
            lv_label_set_text(setting_button_label, "Save");

    return setting_entry;
}

lv_obj_t* build_settings_network_options(lv_obj_t* parent)
{
    lv_obj_t* network_settings = lv_obj_create(parent);
    apply_main_style(network_settings);
    lv_obj_set_size(network_settings, lv_pct(100), lv_pct(80));
    lv_obj_set_flex_flow(network_settings, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_border_opa(network_settings, 0, 0);
    //lv_obj_remove_flag(network_settings, LV_OBJ_FLAG_SCROLLABLE);

        keyboard = create_keyboard(network_settings);

        lv_obj_t* settings_network_wifi_settings = build_settings_section(network_settings, "Network Settings");

            lv_obj_t* wifi_options = lv_obj_create(settings_network_wifi_settings);
            lv_obj_set_flex_flow(wifi_options, LV_FLEX_FLOW_COLUMN);
            apply_main_style(wifi_options);
            lv_obj_set_size(wifi_options, lv_pct(100), lv_pct(40));
            lv_obj_set_style_border_opa(wifi_options, 0, 0);
            lv_obj_remove_flag(wifi_options, LV_OBJ_FLAG_SCROLLABLE);
            

                lv_obj_t* settings_wifi_header = lv_label_create(wifi_options);
                apply_header_sm_label_style(settings_wifi_header);
                lv_label_set_text(settings_wifi_header, "Wifi");

                lv_obj_t* wifi_ssid_widgets = build_settings_entry(wifi_options, "SSID", settings.wifi_ssid, settings_wifi_ssid_cb);


                lv_obj_t* wifi_pass_widgets = build_settings_entry(wifi_options, "Pass", settings.wifi_pass, settings_wifi_ssid_cb);


            lv_obj_t* mqtt_options = lv_obj_create(settings_network_wifi_settings);
            lv_obj_set_flex_flow(mqtt_options, LV_FLEX_FLOW_COLUMN);
            lv_obj_set_size(mqtt_options, lv_pct(100), lv_pct(40));
            apply_main_style(mqtt_options);
            lv_obj_set_style_border_opa(mqtt_options, 0, 0);

                lv_obj_t* settings_mqtt_header = lv_label_create(mqtt_options);
                apply_header_sm_label_style(settings_mqtt_header);
                lv_label_set_text(settings_mqtt_header, "MQTT");

                lv_obj_t* mqtt_address_widgets = build_settings_entry(mqtt_options, "MQTT Address", settings.mqtt_address, settings_wifi_ssid_cb);



    return network_settings;
}

static void settings_wifi_ssid_cb(lv_event_t *e)
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