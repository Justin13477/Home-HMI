#include "data_handlers.h"

void sensor_veml770_data_handler(app_data_t *data, const char* payload, uint32_t length)
{
    // add logs 
    if(data == NULL || payload == NULL || length == 0)
        return;
    cJSON *root = cJSON_ParseWithLength(payload, length);

    if(root == NULL)
        return;
    
    cJSON *lux_value = cJSON_GetObjectItemCaseSensitive(root, "lux");

    if(cJSON_IsNumber(lux_value))
    {
        ESP_LOGI("veml7700_data_handler", "Data Received");
        data->sensors->lux = (float)lux_value->valuedouble;
    }
    cJSON_Delete(root);
}

void sensor_veml770_state_handler(app_data_t *data, const char* payload, uint32_t length)
{
    // add logs 
    if(data == NULL || payload == NULL || length == 0)
        return;
    cJSON *root = cJSON_ParseWithLength(payload, length);

    if(root == NULL)
        return;
    
    cJSON *state_value = cJSON_GetObjectItemCaseSensitive(root, "state");

    if(cJSON_IsNumber(state_value))
    {
        ESP_LOGI("veml7700_data_handler", "Data Received");
        data->sensors->veml7700_state = state_value->valueint;
    }
    cJSON_Delete(root);
}

void sensor_sht41_data_handler(app_data_t *data, const char* payload, uint32_t length)
{
    // add logs 
    ESP_LOGI("sht41", "Calling Handler");
    if(data == NULL || payload == NULL || length == 0)
        return;
    cJSON *root = cJSON_ParseWithLength(payload, length);

    if(root == NULL)
        return;
    
    cJSON *temp_value = cJSON_GetObjectItemCaseSensitive(root, "temp");
    cJSON *hum_value = cJSON_GetObjectItemCaseSensitive(root, "hum");
    ESP_LOGI("sht41_data_handler", "Data Received");

    if(cJSON_IsNumber(temp_value))
    {
        data->sensors->temp = (float)temp_value->valuedouble;
    }
    if(cJSON_IsNumber(temp_value))
    {
        ESP_LOGI("sht41_data_handler", "Data Received");
        data->sensors->hum = (float)hum_value->valuedouble;
    }
    cJSON_Delete(root);
}

void sensor_sht41_state_handler(app_data_t *data, const char* payload, uint32_t length)
{
    // add logs 
    if(data == NULL || payload == NULL || length == 0)
        return;
    cJSON *root = cJSON_ParseWithLength(payload, length);

    if(root == NULL)
        return;
    
    cJSON *state_value = cJSON_GetObjectItemCaseSensitive(root, "state");

    if(cJSON_IsNumber(state_value))
    {
        ESP_LOGI("veml7700_data_handler", "Data Received");
        data->sensors->sht41_state = state_value->valueint;
    }
    cJSON_Delete(root);
}