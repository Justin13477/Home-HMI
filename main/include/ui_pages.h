#ifndef UI_PAGES_H
#define UI_PAGES_H

#include "ui_build.h"

extern lv_obj_t* main_page;
extern lv_obj_t* settings_page;

typedef lv_obj_t* (*page_builder)();

lv_obj_t* build_page(lv_obj_t* page, page_builder builder);

lv_obj_t* build_persistent_ui(lv_obj_t* parent);
lv_obj_t* build_main_page();
lv_obj_t* build_settings_page();

#endif