#include "ui_build.h"

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
lv_obj_t* build_nav_button_power(lv_obj_t* parent)
{
    return build_nav_button_base(parent, LV_SYMBOL_POWER, "Power", set_page_home);
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

lv_obj_t* build_flashcard_content_base1(lv_obj_t* parent, const char* label1, const char* label2)
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
        lv_label_set_text(flashcard_content_label2, label2);

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
        lv_obj_t* flashcard_temp_content_bedroom = build_flashcard_content_base1(flashcard_temp_content, "Bedroom", "73");
        lv_obj_set_size(flashcard_temp_content_bedroom, lv_pct(100), lv_pct(30));


        lv_obj_t* flashcard_temp_content_bathroom = build_flashcard_content_base1(flashcard_temp_content, "Bathroom", "71");
        lv_obj_set_size(flashcard_temp_content_bathroom, lv_pct(100), lv_pct(30));

        lv_obj_t* flashcard_temp_content_living_room = build_flashcard_content_base1(flashcard_temp_content, "Living Room", "76");
        lv_obj_set_size(flashcard_temp_content_living_room, lv_pct(100), lv_pct(30));

        lv_obj_t* flashcard_temp_content_kitchen = build_flashcard_content_base1(flashcard_temp_content, "Kitchen", "75");
        lv_obj_set_size(flashcard_temp_content_kitchen, lv_pct(100), lv_pct(30));

        lv_obj_t* flashcard_temp_content_2nd_bedroom = build_flashcard_content_base1(flashcard_temp_content, "2nd Bedroom", "76");
        lv_obj_set_size(flashcard_temp_content_2nd_bedroom, lv_pct(100), lv_pct(30));

        lv_obj_t* flashcard_temp_content_washroom = build_flashcard_content_base1(flashcard_temp_content, "Washroom", "73");
        lv_obj_set_size(flashcard_temp_content_washroom, lv_pct(100), lv_pct(30));

        lv_obj_t* flashcard_temp_content_mudroom = build_flashcard_content_base1(flashcard_temp_content, "Mudroom", "74");
        lv_obj_set_size(flashcard_temp_content_mudroom, lv_pct(100), lv_pct(30));

    return flashcard_temp_content;
}

lv_obj_t* build_flashcard_temp(lv_obj_t* parent)
{
    return build_flashcard_base(parent, LV_SYMBOL_WARNING, "Temp", build_flashcard_temp_content);
}

lv_obj_t* build_flashcard_lumen_content(lv_obj_t* parent)
{
    lv_obj_t* flashcard_lumen_content = lv_obj_create(parent);
    apply_main_style(flashcard_lumen_content);
    lv_obj_set_size(flashcard_lumen_content, lv_pct(100), lv_pct(65));
    lv_obj_set_flex_flow(flashcard_lumen_content, LV_FLEX_FLOW_COLUMN);  
    lv_obj_set_style_border_opa(flashcard_lumen_content, LV_OPA_0, 0);

        lv_obj_t* flashcard_lumen_content_bedroom = build_flashcard_content_base1(flashcard_lumen_content, "Bedroom", "73");
        lv_obj_set_size(flashcard_lumen_content_bedroom, lv_pct(100), lv_pct(30));

        lv_obj_t* flashcard_lumen_content_bathroom = build_flashcard_content_base1(flashcard_lumen_content, "Bathroom", "71");
        lv_obj_set_size(flashcard_lumen_content_bathroom, lv_pct(100), lv_pct(30));

        lv_obj_t* flashcard_lumen_content_living_room = build_flashcard_content_base1(flashcard_lumen_content, "Living Room", "76");
        lv_obj_set_size(flashcard_lumen_content_living_room, lv_pct(100), lv_pct(30));

        lv_obj_t* flashcard_lumen_content_kitchen = build_flashcard_content_base1(flashcard_lumen_content, "Kitchen", "75");
        lv_obj_set_size(flashcard_lumen_content_kitchen, lv_pct(100), lv_pct(30));

        lv_obj_t* flashcard_lumen_content_2nd_bedroom = build_flashcard_content_base1(flashcard_lumen_content, "2nd Bedroom", "76");
        lv_obj_set_size(flashcard_lumen_content_2nd_bedroom, lv_pct(100), lv_pct(30));

        lv_obj_t* flashcard_lumen_content_washroom = build_flashcard_content_base1(flashcard_lumen_content, "Washroom", "73");
        lv_obj_set_size(flashcard_lumen_content_washroom, lv_pct(100), lv_pct(30));

        lv_obj_t* flashcard_lumen_content_mudroom = build_flashcard_content_base1(flashcard_lumen_content, "Mudroom", "74");
        lv_obj_set_size(flashcard_lumen_content_mudroom, lv_pct(100), lv_pct(30));

    return flashcard_lumen_content;
}

lv_obj_t* build_flashcard_lumen(lv_obj_t* parent)
{
    return build_flashcard_base(parent, LV_SYMBOL_EYE_OPEN, "Lumen", build_flashcard_lumen_content);
}
