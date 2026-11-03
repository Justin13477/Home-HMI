#include "main.h"
#include "state_data_manager.h"

void app_main(void)
{
    MAIN_INFO("Starting LED control application...");

    if (xTaskCreate(run, "page_switcher", 4096, NULL, 5, NULL) != pdPASS) {
        MAIN_ERROR("Failed to create page switcher task");
    }
}
