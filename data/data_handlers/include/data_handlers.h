#include "datatypes.h"
#include "cJSON.h"
#include "esp_err.h"
#include "esp_log.h"

void bedroom_sensor_veml770_data_handler(app_data_t *data, const char* payload, uint32_t length);
void bedroom_sensor_veml770_state_handler(app_data_t *data, const char* payload, uint32_t length);

void bedroom_sensor_sht41_data_handler(app_data_t *data, const char* payload, uint32_t length);
void bedroom_sensor_sht41_state_handler(app_data_t *data, const char* payload, uint32_t length);