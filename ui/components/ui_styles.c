#include "ui_styles.h"

lv_style_t style_base;
lv_style_t style_main;
lv_style_t style_flashcard;

lv_style_t style_nav_button;
lv_style_t style_nav_button_pressed;

lv_style_t style_nav_button_prim_label;
lv_style_t style_nav_button_icon_label;

lv_style_t style_header_big_label;
lv_style_t style_header_sm_label;

lv_style_t style_flashcard_button;
lv_style_t style_flashcard_button_pressed;


lv_style_t style_textarea;
lv_style_t style_textarea_focused;
lv_style_t style_textarea_cursor;

lv_style_t style_bar_green;
lv_style_t style_bar_red;
lv_style_t style_bar_yellow;
lv_style_t style_bar_blue;


lv_style_t style_arc_indicator;


lv_style_t style_spinbox;
lv_style_t style_spinbox_button_icon;


void init_styles()
{
    init_base_style(&style_base);
    init_main_style(&style_main);
    init_flashcard_style(&style_flashcard);

    init_nav_button_style(&style_nav_button);
    init_nav_button_pressed_style(&style_nav_button_pressed);

    init_nav_button_prim_label_style(&style_nav_button_prim_label);
    init_nav_button_icon_label_style(&style_nav_button_icon_label);

    init_header_big_label_style(&style_header_big_label);
    init_header_sm_label_style(&style_header_sm_label);

    init_flashcard_button_style(&style_flashcard_button);
    init_flashcard_button_pressed_style(&style_flashcard_button_pressed);

    init_textarea_style(&style_textarea);
    init_textarea_focused_style(&style_textarea_focused);
    init_textarea_cursor_style(&style_textarea_cursor);

    init_bar_green_style(&style_bar_green);
    init_bar_red_style(&style_bar_red);
    init_bar_yellow_style(&style_bar_yellow);
    init_bar_blue_style(&style_bar_blue);

    init_arc_indicator_style(&style_arc_indicator);
}

void init_base_style(lv_style_t *style)
{
    lv_style_init(style);


        // spacing
        lv_style_set_pad_all(style, 5);

        // color
        lv_style_set_bg_color(style, lv_color_hex(COLOR_MAIN_BG));
        //lv_style_set_bg_grad_color(style, lv_color_hex(COLOR_SEC_BG));
        //lv_style_set_bg_grad_dir(style, LV_GRAD_DIR_VER);
       // lv_style_set_bg_opa(style, LV_OPA_COVER);

        lv_style_set_border_width(style, 5);
}

void apply_base_style(lv_obj_t *obj)
{
    lv_obj_add_style(obj, &style_base, 0);
}

void init_main_style(lv_style_t *style)
{
    lv_style_init(style);

        lv_style_set_bg_color(style, lv_color_hex(COLOR_MAIN_BG));
        lv_style_set_bg_opa(style, LV_OPA_50);

        lv_style_set_pad_all(style, 5);
        lv_style_set_border_width(style, 2);
        lv_style_set_border_color(style, lv_color_hex(COLOR_SEC_BG));
        

        lv_style_set_radius(&style_main, 20);
}

void apply_main_style(lv_obj_t *obj)
{
    lv_obj_add_style(obj, &style_main, 0);
}

void init_flashcard_style(lv_style_t *style)
{
    lv_style_init(style);

        lv_style_set_bg_color(style, lv_color_hex(COLOR_PRIM_S));
        lv_style_set_bg_opa(style, LV_OPA_0);

        lv_style_set_border_width(style, 2);
        lv_style_set_border_color(style, lv_color_hex(COLOR_BORDER));
        lv_style_set_pad_all(style, 5);
        

        lv_style_set_radius(&style_main, 20);
}

void apply_flashcard_style(lv_obj_t *obj)
{
    lv_obj_add_style(obj, &style_flashcard, 0);
}



void init_nav_button_style(lv_style_t *style)
{
    lv_style_init(style);

        lv_style_set_layout(style, LV_LAYOUT_FLEX);
        lv_style_set_flex_flow(style, LV_FLEX_FLOW_COLUMN);
        lv_style_set_flex_main_place(style, LV_FLEX_ALIGN_CENTER);
        lv_style_set_flex_cross_place(style, LV_FLEX_ALIGN_CENTER);
        lv_style_set_flex_track_place(style, LV_FLEX_ALIGN_CENTER);

        lv_style_set_bg_color(style, lv_color_hex(COLOR_PRIM_S));
        lv_style_set_bg_opa(style, LV_OPA_0);

        
        lv_style_set_border_width(style, 0);
        lv_style_set_border_color(style, lv_color_hex(COLOR_BORDER));
        lv_style_set_pad_all(style, 5);
}

void apply_nav_button_style(lv_obj_t *obj)
{
    lv_obj_add_style(obj, &style_nav_button, LV_STATE_DEFAULT | LV_PART_MAIN);
    apply_nav_button_pressed_style(obj);
}

void init_nav_button_pressed_style(lv_style_t *style)
{
    lv_style_init(style);
        lv_style_set_bg_color(style, lv_color_hex(COLOR_HOVER_PRESSED));
        lv_style_set_shadow_color(style, lv_color_hex(COLOR_PRIM_AC));
        lv_style_set_shadow_width(style, 2);
        lv_style_set_shadow_spread(style, 4);
}

void apply_nav_button_pressed_style(lv_obj_t *obj)
{
    lv_obj_add_style(obj, &style_nav_button_pressed, LV_STATE_PRESSED);
}

void init_nav_button_prim_label_style(lv_style_t *style)
{
    lv_style_init(style);
        lv_style_set_bg_opa(style, LV_OPA_0);
        lv_style_set_text_color(style, lv_color_hex(COLOR_PRIM_TEXT));
        lv_style_set_align(style, LV_ALIGN_CENTER);
}

void apply_nav_button_prim_label_style(lv_obj_t * obj)
{
    lv_obj_add_style(obj, &style_nav_button_prim_label, 0);
}

void init_nav_button_icon_label_style(lv_style_t *style)
{
    lv_style_init(style);
        lv_style_set_text_font(style, &lv_font_montserrat_42);
        lv_style_set_bg_opa(style, LV_OPA_0);
        lv_style_set_text_color(style, lv_color_hex(COLOR_PRIM_TEXT));
       
        
}

void apply_nav_button_icon_label_style(lv_obj_t *obj)
{
    lv_obj_add_style(obj, &style_nav_button_icon_label, 0);
}

void init_header_big_label_style(lv_style_t * style)
{
    lv_style_init(style);
        lv_style_set_text_font(style, &lv_font_montserrat_30);
        lv_style_set_bg_opa(style, LV_OPA_0);
        lv_style_set_text_color(style, lv_color_hex(COLOR_PRIM_TEXT));
}

void apply_header_big_label_style(lv_obj_t* obj)
{
    lv_obj_add_style(obj, &style_header_big_label, 0);
}

void init_header_sm_label_style(lv_style_t *style)
{
    
    lv_style_init(style);
        lv_style_set_text_font(style, &lv_font_montserrat_14);
        lv_style_set_bg_opa(style, LV_OPA_0);
        lv_style_set_text_color(style, lv_color_hex(COLOR_SEC_TEXT));
}

void apply_header_sm_label_style(lv_obj_t* obj)
{
    lv_obj_add_style(obj, &style_header_sm_label, 0);
}

void init_flashcard_button_style(lv_style_t *style)
{
    lv_style_init(style);
        lv_style_set_bg_color(style, lv_color_hex(COLOR_MAIN_BG));
        lv_style_set_border_opa(style, 0);
        lv_style_set_border_side(style, LV_BORDER_SIDE_BOTTOM);
        lv_style_set_flex_flow(style, LV_FLEX_FLOW_ROW);
        
}

void apply_flashcard_button_style(lv_obj_t *obj)
{
    lv_obj_add_style(obj, &style_flashcard_button, LV_STATE_DEFAULT | LV_PART_MAIN);
    apply_flashcard_button_pressed_style(obj);
}

void init_flashcard_button_pressed_style(lv_style_t * style)
{
    lv_style_init(style);
        //lv_style_set_bg_color(style, lv_color_hex(COLOR_HOVER_PRESSED));
        lv_style_set_shadow_color(style, lv_color_hex(COLOR_PRIM_AC));
        lv_style_set_shadow_width(style, 2);
        lv_style_set_shadow_spread(style, 4);
}

void apply_flashcard_button_pressed_style(lv_obj_t *obj)
{
    lv_obj_add_style(obj, &style_flashcard_button_pressed, LV_STATE_PRESSED);
}

void init_textarea_style(lv_style_t* style)
{
    lv_style_init(style);
        lv_style_set_bg_color(style, lv_color_hex(COLOR_PRIM_S));
        lv_style_set_border_width(style, 2);
        lv_style_set_border_color(style, lv_color_hex(COLOR_BORDER));

        lv_style_set_radius(style, 8);
}

void apply_textarea_style(lv_obj_t* obj)
{
    lv_obj_add_style(obj, &style_textarea, LV_STATE_DEFAULT);
    apply_textarea_focused_style(obj);
    apply_textarea_cursor_style(obj);
}

void init_textarea_focused_style(lv_style_t* style)
{
    lv_style_init(style);
        lv_style_set_bg_color(style, lv_color_hex(COLOR_ELEVATED_S));
        lv_style_set_shadow_color(style, lv_color_hex(COLOR_PRIM_AC));
        lv_style_set_shadow_width(style, 2);
        lv_style_set_shadow_spread(style, 2);
        lv_style_set_text_color(style, lv_color_hex(COLOR_PRIM_TEXT));
        
}

void apply_textarea_focused_style(lv_obj_t* obj)
{
    lv_obj_add_style(obj, &style_textarea_focused, LV_PART_MAIN | LV_STATE_FOCUSED);
}

void init_textarea_cursor_style(lv_style_t* style)
{
    lv_style_init(style);

        lv_style_set_border_color(style,
                                lv_color_hex(COLOR_PRIM_AC));

        lv_style_set_border_width(style, 2);
        lv_style_set_border_side(style,
                                LV_BORDER_SIDE_LEFT);
        lv_style_set_border_opa(style, LV_OPA_COVER);
}


void apply_textarea_cursor_style(lv_obj_t* obj)
{
    lv_obj_add_style(obj, &style_textarea_cursor, LV_PART_CURSOR | LV_STATE_FOCUSED);
}


void init_bar_green_style(lv_style_t* style)
{
    lv_style_init(style);
    lv_style_set_bg_color(style, lv_color_hex(COLOR_SUCCESS));
}

void apply_bar_green_style(lv_obj_t* obj)
{
    lv_obj_add_style(obj, &style_bar_green, LV_PART_INDICATOR);
}

void init_bar_red_style(lv_style_t* style)
{
    lv_style_init(style);
    lv_style_set_bg_color(style, lv_color_hex(COLOR_ERROR));
}

void apply_bar_red_style(lv_obj_t* obj)
{
    lv_obj_add_style(obj, &style_bar_red, LV_PART_INDICATOR);
}

void init_bar_yellow_style(lv_style_t* style)
{
    lv_style_init(style);
    lv_style_set_bg_color(style, lv_color_hex(COLOR_WARNING));
}

void apply_bar_yellow_style(lv_obj_t* obj)
{
    lv_obj_add_style(obj, &style_bar_yellow, LV_PART_INDICATOR);
    
}

void init_bar_blue_style(lv_style_t* style)
{
    lv_style_init(style);
    lv_style_set_bg_color(style, lv_color_hex(COLOR_PRIM_AC));
}

void apply_bar_blue_style(lv_obj_t* obj)
{
    lv_obj_add_style(obj, &style_bar_blue, LV_PART_INDICATOR);
}

void init_arc_indicator_style(lv_style_t* style)
{
    lv_style_init(style);
        lv_style_set_arc_opa(style, LV_OPA_COVER);
        lv_style_set_arc_color(style, lv_color_hex(COLOR_PRIM_AC));
    
}

void apply_arc_indicator_style(lv_obj_t* obj)
{
    lv_obj_add_style(obj, &style_arc_indicator, LV_PART_INDICATOR);
}


void init_spinbox_style(lv_style_t* style)
{
    lv_style_init(style);
}

void apply_spinbox_style(lv_obj_t* obj)
{

}

void init_spinbox_button_icon_style(lv_style_t* style)
{
    lv_style_init(style);
        lv_style_set_text_font(style, &lv_font_montserrat_24);
        lv_style_set_bg_opa(style, LV_OPA_0);
        lv_style_set_text_color(style, lv_color_hex(COLOR_PRIM_TEXT));
}

void apply_spinbox_button_icon_style(lv_obj_t* obj)
{
    lv_obj_add_style(obj, &style_spinbox_button_icon, 0);
        
}

