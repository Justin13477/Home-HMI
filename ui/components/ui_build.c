#include "ui_build.h"
#include "assets-src.h"
#include <string.h>

app_data_t *ui_build_snapshot;


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



lv_obj_t* ui_build_create_keyboard(lv_obj_t* parent)
{
    lv_obj_t* keyboard = lv_keyboard_create(parent);
    lv_obj_set_size(keyboard, lv_pct(80), lv_pct(40));
    //lv_obj_add_flag(keyboard, LV_OBJ_FLAG_IGNORE_LAYOUT);
    apply_main_style(keyboard);
    

    return keyboard;
}

void init_handlers(ui_page_switcher_cb_t cb)
{
    set_handler_cb(cb);
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

lv_obj_t* build_nav_button_base(lv_obj_t* parent, const char* base_icon, const lv_image_dsc_t *custom_icon, const char* text, lv_event_cb_t cb)
{
    lv_obj_t* button = lv_button_create(parent);
    apply_nav_button_style(button);
    lv_obj_set_style_size(button, lv_pct(100), lv_pct(19), LV_STATE_DEFAULT);
    lv_obj_add_event_cb(button, cb, LV_EVENT_CLICKED, NULL);
    lv_obj_set_flex_flow(button, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(button, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        
        if(custom_icon == NULL)
            {
                lv_obj_t* icon_label = lv_label_create(button);
                apply_nav_button_icon_label_style(icon_label);
                lv_label_set_text(icon_label, base_icon);
            }
        else 
        {
            lv_obj_t* icon_img = lv_image_create(button);
            lv_image_set_src(icon_img, custom_icon);
            lv_obj_set_size(icon_img, 96, 60);
        }
        

        lv_obj_t* text_label = lv_label_create(button);
        apply_nav_button_prim_label_style(text_label);
        lv_label_set_text(text_label, text);
    return button;
}

lv_obj_t* build_nav_button_home(lv_obj_t* parent)
{
    return build_nav_button_base(parent, LV_SYMBOL_HOME, NULL, "Home", set_page_home);
}

lv_obj_t* build_nav_button_settings(lv_obj_t* parent)
{
    return build_nav_button_base(parent, LV_SYMBOL_SETTINGS, NULL, "Settings", set_page_settings);
}
lv_obj_t* build_nav_button_lighting(lv_obj_t* parent)
{
    return build_nav_button_base(parent, LV_SYMBOL_POWER, NULL, "Lighting", set_page_lighting);
}

lv_obj_t* build_nav_button_climate(lv_obj_t* parent)
{
    return build_nav_button_base(parent, LV_SYMBOL_POWER, &thermometer_96, "Climate", set_page_climate);
}



lv_obj_t* build_header_ribbon_page_base(lv_obj_t* parent, const char* base_icon, const lv_image_dsc_t *custom_icon, const char* label, const char* dsc)
{
    lv_obj_t* page_contents = lv_obj_create(parent);
    apply_main_style(page_contents);
    lv_obj_set_style_border_opa(page_contents, LV_OPA_0, 0);
    lv_obj_set_flex_flow(page_contents, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(page_contents, 
                        LV_FLEX_ALIGN_START, 
                        LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER);

    lv_obj_set_size(page_contents, lv_pct(20), lv_pct(100));
        if(custom_icon == NULL)
        {
            lv_obj_t* page_contents_icon_label = lv_label_create(page_contents);
            lv_label_set_text(page_contents_icon_label, base_icon); 
            apply_nav_button_icon_label_style(page_contents_icon_label);
            lv_obj_center(page_contents_icon_label);
        }
        else {
            lv_obj_t* page_contents_icon_img = lv_image_create(page_contents);
            lv_image_set_src(page_contents_icon_img, custom_icon);
        }
        

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
    return build_header_ribbon_page_base(parent, LV_SYMBOL_HOME, NULL, "Home", "Overview");
}
lv_obj_t* build_header_ribbon_page_settings(lv_obj_t* parent)
{
    return build_header_ribbon_page_base(parent, LV_SYMBOL_SETTINGS, NULL, "Settings", "Mixin Shit Up");
}

lv_obj_t* build_header_ribbon_page_climate(lv_obj_t* parent)
{
    return build_header_ribbon_page_base(parent, LV_SYMBOL_AUDIO, &thermometer_96, "Climate", "Air Shenanigans");
}

lv_obj_t* build_header_ribbon_page_lighting(lv_obj_t* parent)
{
    return build_header_ribbon_page_base(parent, LV_SYMBOL_POWER, NULL, "Lighting", "Disco Mode");
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
        lv_obj_remove_style(page_contents, NULL, LV_PART_SCROLLBAR);
        lv_obj_remove_flag(page_contents, LV_OBJ_FLAG_SCROLLABLE);

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
        lv_label_set_text(ribbon_timestamp_label_date, ui_build_snapshot->dtime->time);

        lv_obj_t* ribbon_timestamp_label_time = lv_label_create(ribbon_timestamp);
        apply_header_sm_label_style(ribbon_timestamp_label_time);
        lv_label_set_text(ribbon_timestamp_label_time, ui_build_snapshot->dtime->date);
    return ribbon_timestamp;
}



lv_obj_t* build_flashcard_base(lv_obj_t* parent, const char* icon, const char* label, obj_func_t content_func, lv_event_cb_t cb)                           
{
    lv_obj_t* flashcard = lv_image_create(parent);
    lv_obj_set_size(flashcard, lv_pct(49), lv_pct(48));
    apply_flashcard_style(flashcard);
    lv_obj_set_flex_flow(flashcard, LV_FLEX_FLOW_COLUMN);

        lv_obj_t* flashcard_header = lv_button_create(flashcard);
        lv_obj_set_size(flashcard_header, lv_pct(100), lv_pct(29));
        apply_flashcard_button_style(flashcard_header);
        lv_obj_add_event_cb(flashcard_header, cb, LV_EVENT_CLICKED, NULL);
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

lv_obj_t* build_flashcard_content_base1(lv_obj_t* parent, const char* label1, float num, uint8_t state)
{
    
    lv_obj_t* flashcard_content = lv_obj_create(parent);
    apply_main_style(flashcard_content);
    lv_obj_set_size(flashcard_content, lv_pct(100), lv_pct(38));

    lv_obj_remove_flag(flashcard_content, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_left(flashcard_content, 20, 0);
    lv_obj_set_style_pad_right(flashcard_content, 20, 0);
    lv_obj_set_flex_flow(flashcard_content, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(flashcard_content, 
                        LV_FLEX_ALIGN_SPACE_BETWEEN, 
                        LV_FLEX_ALIGN_CENTER, 
                        LV_FLEX_ALIGN_CENTER);

        lv_obj_t* flashcard_left = lv_obj_create(flashcard_content);
        apply_main_style(flashcard_left);
        lv_obj_set_style_border_opa(flashcard_left, 0, 0);
        lv_obj_remove_flag(flashcard_left, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_remove_style(flashcard_left, NULL, LV_PART_SCROLLBAR);
        lv_obj_set_flex_flow(flashcard_left, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(flashcard_left, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_size(flashcard_left, lv_pct(60), lv_pct(100));

            lv_obj_t* flashcard_content_label1 = lv_label_create(flashcard_left);
            apply_header_sm_label_style(flashcard_content_label1);
            
            lv_label_set_text(flashcard_content_label1, label1);

            lv_obj_t* led = lv_led_create(flashcard_left);
            apply_led_style(led);
            lv_obj_set_size(led, 10, 10);

            switch(state)
            {
            case SENSOR_STATUS_ONLINE:
                lv_led_on(led);
                break;
            case SENSOR_STATUS_OFFLINE:
                lv_led_off(led);
                break;
            }

        lv_obj_t* flashcard_content_label2 = lv_label_create(flashcard_content);
        lv_obj_set_style_text_color(flashcard_content_label2, lv_color_hex(COLOR_PRIM_AC), 0);
        apply_header_sm_label_style(flashcard_content_label2);
        update_float_label(flashcard_content_label2, num);


    return flashcard_content;
}

lv_obj_t* build_flashcard_climate_content(lv_obj_t* parent)
{
    sensor_data_t *sensors = ui_build_snapshot->sensors;
    weather_data_t *weather = ui_build_snapshot->weather_data;

    lv_obj_t* flashcard_content = lv_obj_create(parent);
    apply_main_style(flashcard_content);
    lv_obj_set_size(flashcard_content, lv_pct(100), lv_pct(65));
    lv_obj_set_flex_flow(flashcard_content, LV_FLEX_FLOW_COLUMN);  
    lv_obj_set_style_border_opa(flashcard_content, LV_OPA_0, 0);

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

        lv_obj_t* flashcard_temp_content = build_flashcard_content_base1(flashcard_content, "Temp", sensors->temp, sensors->sht41_state);

        lv_obj_t* flashcard_hum_content = build_flashcard_content_base1(flashcard_content, "Hum", sensors->hum, sensors->veml7700_state);

        
        lv_obj_t* weather_content = build_flashcard_content_base1(flashcard_content, "Current Temp", weather->current.temperature, SENSOR_STATUS_ONLINE);

        //lv_obj_t* flashcard_aq_content = build_flashcard_content_base1(flashcard_temp_content, "Temp", sensors->temp, sensors->sht41_state); for air quality





    return flashcard_content;
}

lv_obj_t* build_flashcard_climate(lv_obj_t* parent)
{
    return build_flashcard_base(parent, LV_SYMBOL_WARNING, "Temperature", build_flashcard_climate_content, flashcard_climate_cb);
}




lv_obj_t* build_flashcard_lighting_content(lv_obj_t* parent)
{
    
    lv_obj_t* flashcard_lighting_content = lv_obj_create(parent);
    apply_main_style(flashcard_lighting_content);
    lv_obj_set_size(flashcard_lighting_content, lv_pct(100), lv_pct(65));
    lv_obj_set_flex_flow(flashcard_lighting_content, LV_FLEX_FLOW_COLUMN);  
    lv_obj_set_style_border_opa(flashcard_lighting_content, LV_OPA_0, 0);

        

    return flashcard_lighting_content;
}

lv_obj_t* build_flashcard_lighting(lv_obj_t* parent)
{
    return build_flashcard_base(parent, LV_SYMBOL_EYE_OPEN, "Lighting", build_flashcard_lighting_content, flashcard_lighting_cb);
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

        keyboard = ui_build_create_keyboard(network_settings);

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

lv_obj_t* build_climate_data_bar(lv_obj_t* parent, const char* label, uint32_t value)
{
    char buf[32];
    snprintf(buf, sizeof(buf), "%d", (int)value);

    lv_obj_t* data_base = lv_obj_create(parent);
    apply_main_style(data_base);
    lv_obj_set_size(data_base, lv_pct(45), lv_pct(48));
    lv_obj_set_flex_flow(data_base, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(data_base, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_border_opa(data_base, 0, 0);

        lv_obj_t* data_bar = lv_bar_create(data_base);
        lv_bar_set_mode(data_bar, LV_BAR_MODE_NORMAL);
        lv_bar_set_value(data_bar, value, LV_ANIM_ON);
        lv_obj_set_size(data_bar, 20, 120);

        if(value >= 0 && value < 60)
            apply_bar_blue_style(data_bar);
        else if(value > 60 && value <= 75)
            apply_bar_green_style(data_bar);
        else if(value > 75 && value <= 90)
            apply_bar_yellow_style(data_bar);
        else if(value > 90 && value < 101)
            apply_bar_red_style(data_bar);
        
        

        lv_obj_t* data_info = lv_obj_create(data_base);
        apply_main_style(data_info);
        lv_obj_set_flex_flow(data_info, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(data_info, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_size(data_info, lv_pct(100), lv_pct(25));
        lv_obj_set_style_border_opa(data_info, 0, 0);

            lv_obj_t* data_label = lv_label_create(data_info);
            apply_header_sm_label_style(data_label);
            lv_label_set_text(data_label, label);
            lv_obj_center(data_label);

            lv_obj_t* value_label = lv_label_create(data_info);
            apply_header_sm_label_style(value_label);
            lv_label_set_text(value_label, buf);
            lv_obj_center(value_label);
    return data_base;
}

lv_obj_t* build_climate_data_bar_temp(lv_obj_t* parent)
{
    return build_climate_data_bar(parent, "Temp", (uint32_t)ui_build_snapshot->sensors->temp);
}

lv_obj_t* build_climate_data_bar_hum(lv_obj_t* parent)
{
    return build_climate_data_bar(parent, "Hum", (uint32_t)ui_build_snapshot->sensors->hum);
}

lv_obj_t* build_climate_data_thermastat(lv_obj_t* parent)
{
    // line meter 
    // spinbox

    // get average when more sensors are added

    int temp = (int)ui_build_snapshot->sensors->temp;
    char buf[32];
    snprintf(buf, sizeof(buf), "%d", temp);

    lv_obj_t* thermastat = lv_obj_create(parent);
    apply_main_style(thermastat);
    lv_obj_set_size(thermastat, lv_pct(35), lv_pct(50));
    lv_obj_set_flex_flow(thermastat, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(thermastat, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_border_opa(thermastat, 0, 0);

        

        lv_obj_t* thermastat_arc = lv_arc_create(thermastat);
        lv_obj_set_flex_flow(thermastat_arc, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(thermastat_arc, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_BETWEEN);
        lv_arc_set_value(thermastat_arc, temp);
        lv_obj_remove_style(thermastat_arc, NULL, LV_PART_KNOB);
        lv_obj_remove_flag(thermastat_arc, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_arc_color(thermastat_arc, lv_color_hex(COLOR_SEC_BG), LV_PART_MAIN);

        if(temp >= 0 && temp < 60)
                apply_arc_indicator_blue_style(thermastat_arc);
            else if(temp > 60 && temp <= 75)
                apply_arc_indicator_green_style(thermastat_arc);
            else if(temp > 75 && temp <= 90)
                apply_arc_indicator_yellow_style(thermastat_arc);
            else if(temp > 90 && temp < 101)
                apply_arc_indicator_red_style(thermastat_arc);

            lv_obj_t* arc_temp = lv_label_create(thermastat_arc);
            apply_header_sm_label_style(arc_temp);
            lv_label_set_text(arc_temp, buf);

        lv_obj_t* spinbox = lv_obj_create(thermastat);
        apply_main_style(spinbox);
        lv_obj_set_flex_flow(spinbox, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(spinbox, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_size(spinbox, lv_pct(100), lv_pct(25));
        lv_obj_set_style_border_opa(spinbox, 0, 0);

            lv_obj_t* spinbox_button_dec = lv_button_create(spinbox);
            apply_nav_button_style(spinbox_button_dec);
            lv_obj_set_size(spinbox_button_dec, lv_pct(25), lv_pct(100));
                lv_obj_t* button_dec_icon = lv_label_create(spinbox_button_dec);
                apply_spinbox_button_icon_style(button_dec_icon);
                lv_label_set_text(button_dec_icon, LV_SYMBOL_MINUS);

            lv_obj_t* thermastat_spinbox = lv_spinbox_create(spinbox);
            lv_obj_set_size(thermastat_spinbox, lv_pct(30), lv_pct(85));
            apply_textarea_style(thermastat_spinbox); // spinbox styling is identical to textarea
                


            lv_obj_t* spinbox_button_inc = lv_button_create(spinbox);
            apply_nav_button_style(spinbox_button_inc);
            lv_obj_set_size(spinbox_button_inc, lv_pct(25), lv_pct(100));
                lv_obj_t* button_inc_icon = lv_label_create(spinbox_button_inc);
                apply_spinbox_button_icon_style(button_inc_icon);
                lv_label_set_text(button_inc_icon, LV_SYMBOL_PLUS);

    return thermastat;
}


lv_obj_t* build_climate_contents(lv_obj_t* parent)
{
    lv_obj_t* climate_contents = lv_obj_create(parent);
    apply_main_style(climate_contents);
    lv_obj_set_size(climate_contents, lv_pct(100), lv_pct(80));
    lv_obj_set_flex_flow(climate_contents, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(climate_contents, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_BETWEEN);
    lv_obj_set_style_border_opa(climate_contents, 0, 0);

        lv_obj_t* left_container = lv_obj_create(climate_contents);
        apply_main_style(left_container);
        lv_obj_set_size(left_container, lv_pct(30), lv_pct(100));
        lv_obj_set_flex_flow(left_container, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_flex_align(left_container, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_style_border_opa(left_container, 0, 0);
        
            lv_obj_t* temp_bar = build_climate_data_bar_temp(left_container);
    
            lv_obj_t* hum_bar = build_climate_data_bar_hum(left_container);

        lv_obj_t* thermastat = build_climate_data_thermastat(climate_contents);

        lv_obj_t* right_container = lv_obj_create(climate_contents);
        apply_main_style(right_container);
        lv_obj_set_size(right_container, lv_pct(30), lv_pct(100));
        lv_obj_set_flex_flow(right_container, LV_FLEX_FLOW_ROW_WRAP);
        lv_obj_set_flex_align(right_container, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_style_border_opa(right_container, 0, 0);

        lv_obj_t* bar1 = build_climate_data_bar_temp(right_container);
        lv_obj_t* bar2 = build_climate_data_bar_temp(right_container);
        lv_obj_t* bar3 = build_climate_data_bar_temp(right_container);
        lv_obj_t* bar4 = build_climate_data_bar_temp(right_container);
        // air quality bars 
    return climate_contents;


}

lv_obj_t* build_weather_flashcard(lv_obj_t* parent)
{
    weather_data_t *data = ui_build_snapshot->weather_data;

    char temp[32];
    snprintf(temp, sizeof(temp), "%d°F",
             (int)data->current.temperature);

    char feels_like[32];
    snprintf(feels_like, sizeof(feels_like), "Feels Like: %d°F",
             (int)data->current.feels_like);

    char humidity[32];
    snprintf(humidity, sizeof(humidity), "Humidity: %d%%",
             (int)data->current.humidity);

    lv_obj_t* flashcard_bg = lv_image_create(parent);
    lv_image_set_src(flashcard_bg, &gray_bg_400x210);

    lv_obj_set_size(flashcard_bg, lv_pct(49), lv_pct(48));
    lv_obj_update_layout(flashcard_bg);

    lv_obj_add_flag(flashcard_bg, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(flashcard_bg, set_page_weather, LV_EVENT_CLICKED, NULL);

    lv_obj_set_flex_flow(flashcard_bg, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(
        flashcard_bg,
        LV_FLEX_ALIGN_SPACE_EVENLY,
        LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER
    );

    // LEFT SIDE
    lv_obj_t* left = lv_obj_create(flashcard_bg);
    apply_main_style(left);

    lv_obj_set_size(left, lv_pct(46), lv_pct(90));
    lv_obj_set_style_border_opa(left, 0, 0);
    lv_obj_set_style_bg_opa(left, 0, 0);
    lv_obj_set_style_pad_all(left, 0, 0);

    lv_obj_set_flex_flow(left, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(
        left,
        LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER
    );

    lv_obj_t* temp_label = lv_label_create(left);
    apply_header_big_label_style(temp_label);
    lv_label_set_text(temp_label, temp);

    lv_obj_t* additional_info = lv_obj_create(left);
    apply_main_style(additional_info);

    lv_obj_set_size(additional_info, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_border_opa(additional_info, 0, 0);
    lv_obj_set_style_bg_opa(additional_info, 0, 0);
    lv_obj_set_style_pad_all(additional_info, 0, 0);

    lv_obj_set_flex_flow(additional_info, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(
        additional_info,
        LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_START,
        LV_FLEX_ALIGN_CENTER
    );

    lv_obj_t* feels_like_label = lv_label_create(additional_info);
    apply_header_sm_label_style(feels_like_label);
    lv_label_set_text(feels_like_label, feels_like);

    lv_obj_t* humidity_label = lv_label_create(additional_info);
    apply_header_sm_label_style(humidity_label);
    lv_label_set_text(humidity_label, humidity);


    // RIGHT SIDE
    lv_obj_t* right = lv_obj_create(flashcard_bg);
    apply_main_style(right);

    lv_obj_set_size(right, lv_pct(46), lv_pct(90));
    lv_obj_set_style_border_opa(right, 0, 0);
    lv_obj_set_style_bg_opa(right, 0, 0);
    lv_obj_set_style_pad_all(right, 0, 0);

    lv_obj_set_flex_flow(right, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(
        right,
        LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER
    );

    lv_obj_t* icon = lv_image_create(right);
    lv_image_set_src(icon, data->current.weather_code_build.image_data_128);
    lv_obj_set_size(icon, 96, 96);
    lv_obj_set_style_translate_x(icon, -15, LV_PART_MAIN); // Move left 15px
    lv_obj_set_style_translate_y(icon, -12, LV_PART_MAIN); // Move up 12px

    lv_obj_t* code = lv_label_create(right);
    apply_header_sm_label_style(code);
    lv_label_set_text(code, data->current.weather_code_build.label);
    lv_obj_set_style_translate_x(code, -15, LV_PART_MAIN); // Move left 15px
    lv_obj_set_style_translate_y(code, -12, LV_PART_MAIN); // Move up 12px

    return flashcard_bg;
}
lv_obj_t* build_climate_toggle(lv_obj_t* parent) 
{
    lv_obj_t *toggle = lv_obj_create(parent);
        lv_obj_set_size(toggle, 180, 55);
        apply_main_style(toggle);
        lv_obj_set_style_border_opa(toggle, 0, 0);
        lv_obj_remove_style(toggle, NULL, LV_PART_SCROLLBAR);
        lv_obj_add_flag(toggle, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_remove_flag(toggle, LV_OBJ_FLAG_SCROLLABLE);

        lv_obj_set_flex_flow(toggle, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(toggle,
                            LV_FLEX_ALIGN_SPACE_EVENLY,
                            LV_FLEX_ALIGN_CENTER,
                            LV_FLEX_ALIGN_CENTER);

        lv_obj_add_flag(toggle, LV_OBJ_FLAG_IGNORE_LAYOUT);

        lv_obj_t *option_1 = lv_button_create(toggle);
        lv_obj_set_size(option_1, lv_pct(50), lv_pct(100));
        apply_nav_button_style(option_1);
        lv_obj_add_event_cb(option_1, set_page_climate, LV_EVENT_CLICKED, NULL);

        lv_obj_t *label_1 = lv_label_create(option_1);
        lv_label_set_text(label_1, "Climate");
        lv_obj_center(label_1);
        apply_header_sm_label_style(label_1);
        

        lv_obj_t *option_2 = lv_button_create(toggle);
        lv_obj_set_size(option_2, lv_pct(50), lv_pct(100));
        apply_nav_button_style(option_2);
        lv_obj_add_event_cb(option_2, set_page_weather, LV_EVENT_CLICKED, NULL);

        lv_obj_t *label_2 = lv_label_create(option_2);
        lv_label_set_text(label_2, "Forecast");
        lv_obj_center(label_2);
        apply_header_sm_label_style(label_2);
    return toggle;
    }

    lv_obj_t* build_forecast_flashcard(lv_obj_t* parent, weather_data_mode_t mode, uint8_t selector)
    {
        if(parent == NULL)
        {
            ESP_LOGE("ui_build", "Cannot build forecast flashcard with a null parent");
            return NULL;
        }

        if(ui_build_snapshot == NULL || ui_build_snapshot->weather_data == NULL)
        {
            ESP_LOGE("ui_build", "Cannot build forecast flashcard without weather data");
            return NULL;
        }

        if(mode != HOURLY_DATA && mode != DAILY_DATA)
        {
            ESP_LOGE("ui_build", "Invalid forecast flashcard mode: %d", mode);
            return NULL;
        }

        if((mode == HOURLY_DATA && selector >= WEATHER_HOURLY_COUNT) ||
           (mode == DAILY_DATA && selector >= WEATHER_DAILY_COUNT))
        {
            ESP_LOGE("ui_build", "Forecast flashcard selector %u is out of range for mode %d", selector, mode);
            return NULL;
        }

        weather_data_t *weather_data = ui_build_snapshot->weather_data;

        lv_obj_t* flashcard_bg = lv_image_create(parent);
        lv_image_set_src(flashcard_bg, &gray_bg_400x210);
        lv_obj_set_flex_flow(flashcard_bg, LV_FLEX_FLOW_ROW);

        if(mode == HOURLY_DATA)
        {
            weather_hourly_t *hourly = &weather_data->hourly;
            char data_buffer[32];
            lv_obj_t* left_info = lv_obj_create(flashcard_bg);
            apply_main_style(left_info);
            lv_obj_set_flex_flow(left_info, LV_FLEX_FLOW_COLUMN);
            lv_obj_set_flex_align(left_info, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
            lv_obj_set_size(left_info, lv_pct(59), lv_pct(100));
            lv_obj_set_style_border_opa(left_info, 0, 0);
            lv_obj_set_style_bg_opa(left_info, 0, 0);

                snprintf(data_buffer, sizeof(data_buffer), "Is Day: %s", hourly->is_day[selector] ? "true" : "false");
                lv_obj_t* is_day_label = lv_label_create(left_info);
                lv_label_set_text(is_day_label, data_buffer);
                apply_header_sm_label_style(is_day_label);

                snprintf(data_buffer, sizeof(data_buffer), "Temperature: %d°F", (int)hourly->temperature[selector]);
                lv_obj_t* temp_label = lv_label_create(left_info);
                lv_label_set_text(temp_label, data_buffer);
                apply_header_sm_label_style(temp_label);

                snprintf(data_buffer, sizeof(data_buffer), "Feels Like: %d°F", (int)hourly->feels_like[selector]);
                lv_obj_t* feels_like_label = lv_label_create(left_info);
                lv_label_set_text(feels_like_label, data_buffer);
                apply_header_sm_label_style(feels_like_label);

                snprintf(data_buffer, sizeof(data_buffer), "Humidity: %d%%", (int)hourly->humidity[selector]);
                lv_obj_t* humidity_label = lv_label_create(left_info);
                lv_label_set_text(humidity_label, data_buffer);
                apply_header_sm_label_style(humidity_label);

                snprintf(data_buffer, sizeof(data_buffer), "Wind Speed: %d MPH", (int)hourly->wind_speed[selector]);
                lv_obj_t* wind_speed_label = lv_label_create(left_info);
                lv_label_set_text(wind_speed_label, data_buffer);
                apply_header_sm_label_style(wind_speed_label);

                snprintf(data_buffer, sizeof(data_buffer), "Wind Direction: %s", determine_wind_direction(hourly->wind_direction[selector]));
                lv_obj_t* wind_dir_label = lv_label_create(left_info);
                lv_label_set_text(wind_dir_label, data_buffer);
                apply_header_sm_label_style(wind_dir_label);

                snprintf(data_buffer, sizeof(data_buffer), "Wind Gusts: %d MPH", (int)hourly->wind_gusts[selector]);
                lv_obj_t* wind_gusts_label = lv_label_create(left_info);
                lv_label_set_text(wind_gusts_label, data_buffer);
                apply_header_sm_label_style(wind_gusts_label);

                snprintf(data_buffer, sizeof(data_buffer), "Preciptiation Probability: %u%%", (unsigned int)hourly->precipitation_probability[selector]);
                lv_obj_t* precip_prob_label = lv_label_create(left_info);
                lv_label_set_text(precip_prob_label, data_buffer);
                apply_header_sm_label_style(precip_prob_label);

                snprintf(data_buffer, sizeof(data_buffer), "Preciptiation: %.2f", hourly->precipitation[selector]);
                lv_obj_t* precip_label = lv_label_create(left_info);
                lv_label_set_text(precip_label, data_buffer);
                apply_header_sm_label_style(precip_label);

                snprintf(data_buffer, sizeof(data_buffer), "Snow Depth: %.2f cm", hourly->snow_depth[selector]);
                lv_obj_t* snow_depth_label = lv_label_create(left_info);
                lv_label_set_text(snow_depth_label, data_buffer);
                apply_header_sm_label_style(snow_depth_label);

                snprintf(data_buffer, sizeof(data_buffer), "Visibility: %.2f km", hourly->visibility[selector] / 1000.0f);
                lv_obj_t* visibility_label = lv_label_create(left_info);
                lv_label_set_text(visibility_label, data_buffer);
                apply_header_sm_label_style(visibility_label);

            lv_obj_t* right_info = lv_obj_create(flashcard_bg);
            apply_main_style(right_info);
            lv_obj_set_flex_flow(right_info, LV_FLEX_FLOW_COLUMN);
            lv_obj_set_flex_align(right_info, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
            lv_obj_set_size(right_info, lv_pct(40), lv_pct(100));
            lv_obj_set_style_border_opa(right_info, 0, 0);
            lv_obj_set_style_bg_opa(right_info, 0, 0);

                const char *time = strchr(hourly->time[selector], 'T');
                char time_buffer[6];
                if(time != NULL)
                {
                    snprintf(time_buffer, sizeof(time_buffer), "%.5s", time + 1);
                }
                else
                {
                    snprintf(time_buffer, sizeof(time_buffer), "--:--");
                }
                lv_obj_t* time_label = lv_label_create(right_info);
                lv_label_set_text(time_label, time_buffer);
                apply_header_sm_label_style(time_label);

                lv_obj_t* code_icon = lv_image_create(right_info);
                lv_image_set_src(code_icon, hourly->weather_code_build[selector].image_data_128);
                lv_obj_set_style_translate_y(code_icon, -12, LV_PART_MAIN); // Move up 12px

                snprintf(data_buffer, sizeof(data_buffer), "%s", hourly->weather_code_build[selector].label);
                lv_obj_t* code_label = lv_label_create(right_info);
                lv_label_set_text(code_label, data_buffer);
                apply_header_sm_label_style(code_label);
                lv_obj_set_style_translate_y(code_label, -15, LV_PART_MAIN); // Move up 12px
        }

        else if(mode == DAILY_DATA)
        {
            weather_daily_t *daily = &weather_data->daily;
            char data_buffer[32];

            lv_obj_t* left_info = lv_obj_create(flashcard_bg);
            apply_main_style(left_info);
            lv_obj_set_flex_flow(left_info, LV_FLEX_FLOW_COLUMN);
            lv_obj_set_flex_align(left_info, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
            lv_obj_set_size(left_info, lv_pct(59), lv_pct(100));
            lv_obj_set_style_border_opa(left_info, 0, 0);
            lv_obj_set_style_bg_opa(left_info, 0, 0);

                snprintf(data_buffer, sizeof(data_buffer), "Max Temperature: %d°F", (int)daily->temperature_max[selector]);
                lv_obj_t* temp_max_label = lv_label_create(left_info);
                lv_label_set_text(temp_max_label, data_buffer);
                apply_header_sm_label_style(temp_max_label);

                snprintf(data_buffer, sizeof(data_buffer), "Min Temperature: %d°F", (int)daily->temperature_min[selector]);
                lv_obj_t* temp_min_label = lv_label_create(left_info);
                lv_label_set_text(temp_min_label, data_buffer);
                apply_header_sm_label_style(temp_min_label);

                uint32_t daylight_seconds = daily->daylight_duration[selector] > 0.0f
                    ? (uint32_t)daily->daylight_duration[selector]
                    : 0U;
                uint32_t hours = daylight_seconds / 3600U;
                uint32_t minutes = (daylight_seconds % 3600U) / 60U;

                snprintf(data_buffer, sizeof(data_buffer), "Daylight Duration: %uh%02um",
                         (unsigned int)hours, (unsigned int)minutes);
                lv_obj_t* daylight_label = lv_label_create(left_info);
                lv_label_set_text(daylight_label, data_buffer);
                apply_header_sm_label_style(daylight_label);

                const char *time = strchr(daily->sunrise[selector], 'T');
                char sunrise_buffer[24];
                snprintf(sunrise_buffer, sizeof(sunrise_buffer), "Sunrise: %.5s",
                         time != NULL && strlen(time + 1) >= 5 ? time + 1 : "--:--");
                lv_obj_t* sunrise_label = lv_label_create(left_info);
                lv_label_set_text(sunrise_label, sunrise_buffer);
                apply_header_sm_label_style(sunrise_label);

                time = strchr(daily->sunset[selector], 'T');
                char sunset_buffer[24];
                snprintf(sunset_buffer, sizeof(sunset_buffer), "Sunset: %.5s",
                         time != NULL && strlen(time + 1) >= 5 ? time + 1 : "--:--");
                lv_obj_t* sunset_label = lv_label_create(left_info);
                lv_label_set_text(sunset_label, sunset_buffer);
                apply_header_sm_label_style(sunset_label);

            lv_obj_t* right_info = lv_obj_create(flashcard_bg);
            apply_main_style(right_info);
            lv_obj_set_flex_flow(right_info, LV_FLEX_FLOW_COLUMN);
            lv_obj_set_flex_align(right_info, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
            lv_obj_set_size(right_info, lv_pct(40), lv_pct(100));
            lv_obj_set_style_border_opa(right_info, 0, 0);
            lv_obj_set_style_bg_opa(right_info, 0, 0);

                const char *date = daily->date[selector];
            char date_buffer[6];
            if(date[4] == '-' && date[7] == '-' && date[5] != '\0' &&
               date[6] != '\0' && date[8] != '\0' && date[9] != '\0')
            {
                snprintf(date_buffer, sizeof(date_buffer), "%.2s/%.2s", date + 5, date + 8);
            }
            else
            {
                snprintf(date_buffer, sizeof(date_buffer), "--/--");
            }
                lv_obj_t* date_label = lv_label_create(right_info);
            lv_label_set_text(date_label, date_buffer);
                apply_header_sm_label_style(date_label);

                lv_obj_t* code_icon = lv_image_create(right_info);
                lv_image_set_src(code_icon, daily->weather_code_build[selector].image_data_128);
                lv_obj_set_style_translate_y(code_icon, -12, LV_PART_MAIN); // Move up 12px

                snprintf(data_buffer, sizeof(data_buffer), "%s", daily->weather_code_build[selector].label);
                lv_obj_t* code_label = lv_label_create(right_info);
                lv_label_set_text(code_label, data_buffer);
                apply_header_sm_label_style(code_label);
                lv_obj_set_style_translate_y(code_label, -15, LV_PART_MAIN); // Move up 12px
        }

        return flashcard_bg;
    }

    lv_obj_t* build_forecast_contents(lv_obj_t* parent)
    {
        weather_data_t *weather_data = ui_build_snapshot->weather_data;

        lv_obj_t* contents = lv_obj_create(parent);
        lv_obj_set_flex_flow(contents, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_size(contents, lv_pct(100), lv_pct(80));
        apply_main_style(contents);
        lv_obj_set_style_pad_all(contents, 0, 0);
        lv_obj_set_style_border_width(contents, 0, 0);
        lv_obj_remove_style(contents, NULL, LV_PART_SCROLLBAR);
        lv_obj_remove_flag(contents, LV_OBJ_FLAG_SCROLLABLE);

        lv_obj_t* contents_header = lv_obj_create(contents);
        lv_obj_set_size(contents_header, lv_pct(100), lv_pct(5));
        lv_obj_set_style_pad_all(contents_header, 0, 0);
        lv_obj_set_style_border_width(contents_header, 0, 0);
        lv_obj_set_style_bg_opa(contents_header, 0, 0);
        lv_obj_set_style_border_opa(contents_header, 0, 0);

        lv_obj_t* flashcards = lv_obj_create(contents);
        apply_main_style(flashcards);
        lv_obj_set_size(flashcards, lv_pct(100), lv_pct(44));
        lv_obj_set_flex_flow(flashcards, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_pad_all(flashcards, 0, 0);
        lv_obj_set_style_border_width(flashcards, 0, 0);
        //lv_obj_set_style_border_opa(flashcards, 0, 0);

            lv_obj_t* background = build_weather_flashcard(flashcards);
            lv_obj_set_size(background, lv_pct(49), lv_pct(100));

            lv_obj_t* background1 = build_forecast_flashcard(flashcards, HOURLY_DATA, 0);
            lv_obj_set_size(background1, lv_pct(49), lv_pct(100));

        lv_obj_t* background2 = lv_obj_create(contents);
        lv_obj_set_size(background2, lv_pct(100), lv_pct(22));
        apply_main_style(background2);
        lv_obj_set_flex_flow(background2, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_pad_all(background2, 0, 0);
        lv_obj_set_style_border_width(background2, 0, 0);
        lv_obj_set_style_border_opa(background2, 0, 0);
        lv_obj_add_flag(background2, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_scroll_dir(background2, LV_DIR_HOR);
        lv_obj_set_scrollbar_mode(background2, LV_SCROLLBAR_MODE_AUTO);

            lv_obj_t* hourly_displays[WEATHER_HOURLY_COUNT];
            for(int i = 0; i < WEATHER_HOURLY_COUNT; i++)
            {
                const char *time = strchr(weather_data->hourly.time[i], 'T');
                char time_buffer[6];
                if(time != NULL)
                {
                    snprintf(time_buffer, sizeof(time_buffer), "%.5s", time + 1);
                }
                else
                {
                    snprintf(time_buffer, sizeof(time_buffer), "--:--");
                }
                weather_code_build_t* code_build = &weather_data->hourly.weather_code_build[i];
                const lv_image_dsc_t *image = code_build->image_data_48;

                hourly_displays[i] = lv_image_create(background2);
                lv_image_set_src(hourly_displays[i], &gray_bg_120x100);
                lv_obj_set_size(hourly_displays[i], lv_pct(14), lv_pct(100));
                apply_main_style(hourly_displays[i]);
                lv_obj_set_flex_flow(hourly_displays[i], LV_FLEX_FLOW_COLUMN);
                lv_obj_set_flex_align(hourly_displays[i],
                                      LV_FLEX_ALIGN_CENTER,
                                      LV_FLEX_ALIGN_CENTER,
                                      LV_FLEX_ALIGN_CENTER);
                lv_obj_set_style_pad_all(hourly_displays[i], 2, 0);
                lv_obj_set_style_border_width(hourly_displays[i], 1, 0);
                lv_obj_remove_flag(hourly_displays[i], LV_OBJ_FLAG_SCROLLABLE);

                    lv_obj_t* icon_image = lv_image_create(hourly_displays[i]);
                    lv_image_set_src(icon_image, image);
                    lv_obj_set_size(icon_image, 32, 32);
                    lv_image_set_scale(icon_image, 171);

                    char hourly_info[40];
                    snprintf(hourly_info, sizeof(hourly_info), "%s\n%d°F\nRain %u%%",
                             time_buffer,
                             (int)weather_data->hourly.temperature[i],
                             (unsigned int)weather_data->hourly.precipitation_probability[i]);
                    lv_obj_t* hourly_info_label = lv_label_create(hourly_displays[i]);
                    lv_label_set_text(hourly_info_label, hourly_info);
                    lv_obj_set_width(hourly_info_label, lv_pct(100));
                    lv_obj_set_style_text_align(hourly_info_label, LV_TEXT_ALIGN_CENTER, 0);
                    apply_header_sm_label_style(hourly_info_label);

                if((i + 1) % 6 == 0)
                {
                    vTaskDelay(1);
                }
            }


        lv_obj_t* background3 = lv_obj_create(contents);
        lv_obj_set_size(background3, lv_pct(100), lv_pct(22));
        apply_main_style(background3);
        lv_obj_set_flex_flow(background3, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_border_opa(background3, 0, 0);
        lv_obj_set_style_pad_all(background3, 0, 0);
        lv_obj_set_style_border_width(background3, 0, 0);
        lv_obj_set_flex_align(background3,
                              LV_FLEX_ALIGN_SPACE_BETWEEN,
                              LV_FLEX_ALIGN_CENTER,
                              LV_FLEX_ALIGN_CENTER);
        lv_obj_remove_flag(background3, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_t* daily_displays[WEATHER_DAILY_COUNT];
                for(int i = 0; i < WEATHER_DAILY_COUNT; i++)
                {
                    const char *date = weather_data->daily.date[i];
                    char date_buffer[12];
                    snprintf(date_buffer, sizeof(date_buffer), "%.2s/%.2s", date + 5, date + 8);

                    weather_code_build_t* code_build = &weather_data->daily.weather_code_build[i];
                    const lv_image_dsc_t* image = code_build->image_data_48;

                    daily_displays[i] = lv_image_create(background3);
                    lv_image_set_src(daily_displays[i], &gray_bg_120x100);
                    lv_obj_set_size(daily_displays[i], lv_pct(14), lv_pct(100));
                    apply_main_style(daily_displays[i]);
                    lv_obj_set_flex_flow(daily_displays[i], LV_FLEX_FLOW_COLUMN);
                    lv_obj_set_flex_align(daily_displays[i],
                                          LV_FLEX_ALIGN_CENTER,
                                          LV_FLEX_ALIGN_CENTER,
                                          LV_FLEX_ALIGN_CENTER);
                    lv_obj_set_style_pad_all(daily_displays[i], 2, 0);
                    lv_obj_set_style_border_width(daily_displays[i], 1, 0);
                    lv_obj_remove_flag(daily_displays[i], LV_OBJ_FLAG_SCROLLABLE);

                        lv_obj_t* icon_image = lv_image_create(daily_displays[i]);
                        lv_image_set_src(icon_image, image);
                        lv_obj_set_size(icon_image, 36, 36);
                        lv_image_set_scale(icon_image, 192);

                        char daily_info[40];
                        snprintf(daily_info, sizeof(daily_info), "%s\nHigh %d°F\nLow %d°F",
                                 date_buffer,
                                 (int)weather_data->daily.temperature_max[i],
                                 (int)weather_data->daily.temperature_min[i]);
                        lv_obj_t* daily_info_label = lv_label_create(daily_displays[i]);
                        lv_label_set_text(daily_info_label, daily_info);
                        lv_obj_set_width(daily_info_label, lv_pct(100));
                        lv_obj_set_style_text_align(daily_info_label, LV_TEXT_ALIGN_CENTER, 0);
                        apply_header_sm_label_style(daily_info_label);

                if((i + 1) % 6 == 0)
                {
                    vTaskDelay(1);
                }
            }

        return contents;
    }