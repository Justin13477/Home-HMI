#ifndef UI_PAGES_H
#define UI_PAGES_H

#include "ui_build.h"



extern lv_obj_t* main_page;
extern lv_obj_t* settings_page;
extern lv_obj_t* climate_page;
extern lv_obj_t* lighting_page;

typedef lv_obj_t* (*page_builder)(void);

lv_obj_t* build_page(lv_obj_t* page, page_builder builder);

lv_obj_t* build_persistent_ui(lv_obj_t* parent);
lv_obj_t* build_main_page();
lv_obj_t* build_settings_page();
lv_obj_t* build_lighting_page();
lv_obj_t* build_climate_page();

#endif