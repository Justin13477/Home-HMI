#include "main.h"


void app_main(void)
{

    system_init();
    ESP_LOGI(MAIN_TAG, "Starting HMI...");

    if (xTaskCreate(data_task, "data_task", 4096, NULL, 6, NULL) != pdPASS) {
        ESP_LOGE(MAIN_TAG,"Failed to create data_task task");
    }

    if (xTaskCreate(run_task, "page_switcher", 4096, NULL, 5, NULL) != pdPASS) {
        ESP_LOGE(MAIN_TAG,"Failed to create page switcher task");
    }

    if(xTaskCreate(network_task, "network_task", 4096, NULL, 4, NULL) != pdPASS){
        ESP_LOGE(MAIN_TAG,"Failed to create network_task");
    }

    if (xTaskCreate(update_snapshot_task, "update snapshot task", 4096, NULL, 4, NULL) != pdPASS) {
        ESP_LOGE(MAIN_TAG,"Failed to create update_snapshot_task");
    }
    
    if(xTaskCreate(weather_manager_task, "weather_manager_task", 4096, NULL, 4, NULL) != pdPASS)
    {
        ESP_LOGE(MAIN_TAG, "Failed to create weather_manager_task");
    }

    

}
