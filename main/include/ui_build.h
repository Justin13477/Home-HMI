#ifndef UI_BUILD_H
#define UI_BUILD_H

#include "ui_styles.h"
#include "lvgl.h"
#include "state_data_manager.h"

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

typedef lv_obj_t* (*obj_func_t)(lv_obj_t* parent);


lv_obj_t* build_nav_sidebar(lv_obj_t *parent); // take a struct pointer to update state changes via cb
lv_obj_t* build_nav_button_base(lv_obj_t* parent, const char* icon, const char* text, lv_event_cb_t cb);
lv_obj_t* build_nav_button_home(lv_obj_t* parent);
lv_obj_t* build_nav_button_settings(lv_obj_t* parent);
lv_obj_t* build_nav_button_power(lv_obj_t* parent);



lv_obj_t* build_header_ribbon(lv_obj_t* parent, obj_func_t page_contents_func); // take a state variable
lv_obj_t* build_header_ribbon_contents(lv_obj_t* parent, lv_obj_t* page_contents); // take a state variable 
lv_obj_t* build_header_ribbon_page_base(lv_obj_t* parent, const char* icon, const char* label, const char* dsc);
lv_obj_t* build_header_ribbon_page_home(lv_obj_t* parent);
lv_obj_t* build_header_ribbon_page_settings(lv_obj_t* parent);

lv_obj_t* build_header_ribbon_timestamp(lv_obj_t* parent); // take a time and date struct

lv_obj_t* build_flashcard_base(lv_obj_t* parent, const char* icon, const char* label, obj_func_t content_func); // take a pointer to state struct
lv_obj_t* build_flashcard_content_base1(lv_obj_t* parent, const char* label1, const char* label2);

lv_obj_t* build_flashcard_temp(lv_obj_t* parent);
lv_obj_t* build_flashcard_temp_content(lv_obj_t* parent); // take a small struct of temp readings


lv_obj_t* build_flashcard_lumen(lv_obj_t* parent); // small struct for lumen readings
lv_obj_t* build_flashcard_lumen_content(lv_obj_t* parent); // small

#endif

