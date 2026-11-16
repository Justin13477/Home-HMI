#include "datatypes.h"
#include "cJSON.h"
#include "esp_err.h"
#include "esp_log.h"
#include "stdbool.h"

void sensor_veml770_data_handler(app_data_t *data, const char* payload, uint32_t length);
void sensor_veml770_state_handler(app_data_t *data, const char* payload, uint32_t length); // wrap all state handlers to one base handler with an additional parameter to save flash

void sensor_sht41_data_handler(app_data_t *data, const char* payload, uint32_t length); 
void sensor_sht41_state_handler(app_data_t *data, const char* payload, uint32_t length);