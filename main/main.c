#include "main.h"
#include "state_data_manager.h"
#include "ui_build.h"

void app_main(void)
{

    system_init();
    MAIN_INFO("Starting HMI...");

    if (xTaskCreate(run_task, "page_switcher", 4096, NULL, 5, NULL) != pdPASS) {
        MAIN_ERROR("Failed to create page switcher task");
    }
    if (xTaskCreate(data_task, "data_task", 4096, NULL, 5, NULL) != pdPASS) {
        MAIN_ERROR("Failed to create data_task task");
    }
    if (xTaskCreate(update_snapshot_task, "update snapshot task", 4096, NULL, 5, NULL) != pdPASS) {
        MAIN_ERROR("Failed to create update_snapshot_task");
    }
    if(xTaskCreate(network_task, "network_task", 4096, NULL, 5, NULL) != pdPASS)
    {
        MAIN_ERROR("Failed to create network_task");
    }

}
