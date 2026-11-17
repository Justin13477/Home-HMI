#include "storage_manager.h"

static const char* TAG = "STORAGE_MANAGER";

void init_storage()
{
    sd_init();
    ESP_LOGI(TAG, "Initialized successfully");
}