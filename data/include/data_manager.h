#include "data_handlers.h"
#include "mqtt_manager.h"
#include "wifi_manager.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "tag_map.h"



extern settings_t settings; // Settings page directly access this struct
                            // not good design ahhh wellll
                            
extern SemaphoreHandle_t reconnect_sem;

void init_data(); // System Init

app_data_t* get_data_snapshot(); // Getting App Data Snapshot

void data_task(void *arg); // For handling incoming data
void network_task(void *arg); // For handling network events like reconnect
