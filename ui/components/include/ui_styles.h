#ifndef UI_STYLES_H
#define UI_STYLES_H

// Color palette
// BG Colors
#define COLOR_MAIN_BG       0x121418  // Obsidian
#define COLOR_SEC_BG        0x191C22  // Graphite

// Surface Colors
#define COLOR_PRIM_S        0x20242C  // Charcoal
#define COLOR_ELEVATED_S    0x292E38  // Slate
#define COLOR_HOVER_PRESSED 0x343B48  // Steel
#define COLOR_BORDER        0x303641  // Graphite Border

// Typography
#define COLOR_PRIM_TEXT     0xF1F3F5  // Cloud White
#define COLOR_SEC_TEXT      0xA0A8B5  // Silver Gray
#define COLOR_MUTE_TEXT     0x6F7887  // Ash Gray

// Accents
#define COLOR_PRIM_AC       0x5B9DFF  // Electric Blue
#define COLOR_SEC_AC        0x43D9E8  // Cyan

// Status Colors
#define COLOR_SUCCESS       0x4DD4A3  // Mint Green
#define COLOR_WARNING       0xF5B942  // Amber
#define COLOR_ERROR         0xFF647C  // Coral Red

#include "lvgl.h"

extern const lv_image_dsc_t noise_texture1;

// sleek minimalist theme
extern lv_style_t style_base;
extern lv_style_t style_main;

extern lv_style_t style_nav_button;
extern lv_style_t style_nav_button_pressed;

extern lv_style_t style_nav_button_prim_label;
extern lv_style_t style_nav_button_icon_label;

extern lv_style_t style_header_big_label;
extern lv_style_t style_header_sm_label;

// init styles
void init_styles();

// container styles
void init_base_style(lv_style_t *style);
void init_main_style(lv_style_t *style);
void init_flashcard_style(lv_style_t * style);

// init nav button styles
void init_nav_button_styles(lv_style_t *style);
void init_nav_button_style(lv_style_t *style);
void init_nav_button_pressed_style(lv_style_t *style);

// init label style
void init_nav_button_prim_label_style(lv_style_t *style);
void init_nav_button_icon_label_style(lv_style_t *style);

// init generic label styles
void init_header_big_label_style(lv_style_t * style);
void init_header_sm_label_style(lv_style_t *style);


// init flashcard sytles
void init_flashcard_button_style(lv_style_t * style);
void init_flashcard_button_pressed_style(lv_style_t * style);

// text area and keyboard styles
void init_textarea_style(lv_style_t* style);
void init_textarea_focused_style(lv_style_t* style);
void init_textarea_cursor_style(lv_style_t* style);

// apply styles
void apply_base_style(lv_obj_t* obj); // screen style
void apply_main_style(lv_obj_t *obj);   // for front containers
void apply_flashcard_style(lv_obj_t *obj);

// apply button styles
void apply_nav_button_style(lv_obj_t *obj);
void apply_nav_button_pressed_style(lv_obj_t *obj);

// apply label styles
void apply_nav_button_prim_label_style(lv_obj_t *obj);
void apply_nav_button_icon_label_style(lv_obj_t *obj);

void apply_header_big_label_style(lv_obj_t *obj);
void apply_header_sm_label_style(lv_obj_t *obj);

void apply_flashcard_button_pressed_style(lv_obj_t *obj);
void apply_flashcard_button_style(lv_obj_t *obj);

void apply_textarea_style(lv_obj_t* obj);
void apply_textarea_focused_style(lv_obj_t* obj);
void apply_textarea_cursor_style(lv_obj_t* obj);

#endif

