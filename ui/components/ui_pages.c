#include "ui_pages.h"

lv_obj_t* main_page;
lv_obj_t* settings_page;
lv_obj_t* climate_page;
lv_obj_t* lighting_page;
subpage_state_t climate_subpage;

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

                lv_obj_t* climate_flashcard = build_flashcard_climate(flashcard_area);
                lv_obj_t* lighting_flashcard = build_flashcard_lighting(flashcard_area);
                lv_obj_t* weather_flashcard = build_weather_flashcard(flashcard_area);
                


                

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

        
        //lv_obj_move_foreground(page_toggle);

        if(current_subpage_climate == SUBPAGE_CLIMATE)
            {
                lv_obj_t* climate = build_climate_contents(contents);
            }
        else if(current_subpage_climate == SUBPAGE_WEATHER)
            {
                lv_obj_t* forecast = build_forecast_contents(contents);
            }

        lv_obj_t* page_toggle = build_climate_toggle(contents);
        lv_obj_set_x(page_toggle, lv_pct(39));
        lv_obj_set_y(page_toggle, lv_pct(18));
        
    return climate_page;
}