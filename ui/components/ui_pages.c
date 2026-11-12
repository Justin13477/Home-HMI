#include "ui_pages.h"

lv_obj_t* main_page;
lv_obj_t* settings_page;
lv_obj_t* climate_page;
lv_obj_t* lighting_page;

lv_obj_t* build_page(lv_obj_t* page, page_builder builder)
{
    page = builder();
    return page;
};

lv_obj_t* build_persistent_ui(lv_obj_t* parent)
{
    
    apply_base_style(parent);
    lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_pad_row(parent, 0, LV_PART_MAIN);
    

        lv_obj_t *nav_sidebar_h = build_nav_sidebar(parent);

                lv_obj_t* nav_button_home_h = build_nav_button_home(nav_sidebar_h);     
                
                lv_obj_t* nav_button_climate_h = build_nav_button_climate(nav_sidebar_h);

                lv_obj_t* nav_button_lighting_h = build_nav_button_lighting(nav_sidebar_h);

                lv_obj_t* nav_button_settings_h = build_nav_button_settings(nav_sidebar_h);

                


        lv_obj_t* contents = lv_obj_create(parent);
        lv_obj_remove_flag(contents, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_size(contents, lv_pct(84), lv_pct(100));
        lv_obj_set_style_border_opa(contents, LV_OPA_0, 0);
        apply_main_style(contents);
        lv_obj_set_flex_flow(contents, LV_FLEX_FLOW_COLUMN);

            
        keyboard = ui_build_create_keyboard(parent, ui_build_get_keyboard());
        lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_FLOATING);
    return contents;
}

lv_obj_t* build_main_page()
{
    lv_obj_t *main_page = lv_obj_create(NULL);;
    lv_obj_t *contents = build_persistent_ui(main_page);
            
        lv_obj_t* header_ribbon_h = build_header_ribbon(contents, build_header_ribbon_page_home);

            lv_obj_t* flashcard_area = lv_obj_create(contents);
            lv_obj_set_style_border_opa(flashcard_area, LV_OPA_0, 0);
            lv_obj_set_size(flashcard_area, lv_pct(100), lv_pct(78));
            lv_obj_set_flex_flow(flashcard_area, LV_FLEX_FLOW_ROW_WRAP);

            apply_main_style(flashcard_area);

                lv_obj_t* temp_flashcard = build_flashcard_temp(flashcard_area);
                lv_obj_t* hum_flashcard = build_flashcard_hum(flashcard_area);
                lv_obj_t* lumen_flashcard = build_flashcard_lumen(flashcard_area);
                

    return main_page;
}

lv_obj_t* build_settings_page()
{
    lv_obj_t *settings_page = lv_obj_create(NULL);
    lv_obj_t *contents = build_persistent_ui(settings_page);

        lv_obj_t* header_ribbon_h = build_header_ribbon(contents, build_header_ribbon_page_settings);

        lv_obj_t* settings = build_settings_network_options(contents);
    return settings_page;
}

lv_obj_t* build_lighting_page()
{
    lv_obj_t *lighting_page = lv_obj_create(NULL);
    lv_obj_t *contents = build_persistent_ui(lighting_page);

        lv_obj_t* header_ribbon_h = build_header_ribbon(contents, build_header_ribbon_page_lighting);
    return lighting_page;
}
lv_obj_t* build_climate_page()
{
    lv_obj_t *climate_page = lv_obj_create(NULL);
    lv_obj_t *contents = build_persistent_ui(climate_page);

        lv_obj_t* header_ribbon_h = build_header_ribbon(contents, build_header_ribbon_page_climate);

        
    return climate_page;
}