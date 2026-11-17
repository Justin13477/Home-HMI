#include "weather_manager.h"

#include <stdio.h>
#include <string.h>

#include "esp_http_client.h"
#include "esp_crt_bundle.h"
#include "esp_log.h"

static const char* TAG = "WEATHER_MANAGER";

#define WEATHER_URL "https://api.open-meteo.com/v1/forecast?latitude=37.14645&longitude=-94.463&daily=daylight_duration,sunrise,sunset,weather_code&hourly=temperature_2m,relative_humidity_2m,apparent_temperature,precipitation_probability,precipitation,snow_depth,weather_code,visibility,wind_speed_10m,wind_direction_10m,wind_gusts_10m&current=temperature_2m,is_day&timezone=auto&wind_speed_unit=mph&temperature_unit=fahrenheit&precipitation_unit=inch&forecast_hours=24" 

static int response_length = 0;
static char buffer[4096] = {0};

static weather_data_t weather_data = {0};

static esp_err_t http_event_handler(esp_http_client_event_t *evt)
{
    switch(evt->event_id)
    {
        case HTTP_EVENT_ON_DATA:
            {
                size_t incoming = evt->data_len;

            if (response_length + incoming < sizeof(buffer))
            {
                memcpy(
                    buffer + response_length,
                    evt->data,
                    incoming
                );

                response_length += incoming;
                buffer[response_length] = '\0';
            }
        default:
            break;
        }
    }
    return ESP_OK;
}


void weather_manager_init()
{
    
    esp_http_client_config_t config = 
    {
        .url = WEATHER_URL, 
        .method = HTTP_METHOD_GET, 
        .crt_bundle_attach = esp_crt_bundle_attach, 
        .timeout_ms = 10000, 
        .event_handler = http_event_handler
    };

    esp_http_client_handle_t handle = esp_http_client_init(&config);
    ESP_ERROR_CHECK(esp_http_client_perform(handle));

    ESP_LOGI(TAG, "HTTP Status: %d", esp_http_client_get_status_code(handle));

    int64_t content_length = esp_http_client_get_content_length(handle);
    ESP_LOGI(TAG, "Response Length: %", PRId64, content_length);

    ESP_LOGI(TAG, "Response: %s", buffer);

    esp_http_client_cleanup(handle);

    
}

bool weather_manager_get_data(weather_data_t* data)
{
    return weather_data.valid;
}

void parse_weather_data(char* buffer, size_t size, weather_data_t *data)
{
    cJSON *root = cJSON_Parse(buffer);
    if(root == NULL)
    {
        ESP_LOGE(TAG, "Failed to parse weather JSON");
        return;
    }

    cJSON *current = cJSON_GetObjectItem(root, "current");
    if(cJSON_IsObject(current))
    {


        cJSON *temperature = cJSON_GetObjectItemCaseSensitive(current, "temperature_2m");
        if(cJSON_IsNumber(temperature))
        {
            data->current.temperature = (float)temperature->valuedouble;
        }
        cJSON *is_day = cJSON_GetObjectItemCaseSensitive(current, "is_day");
        if(cJSON_IsBool(is_day))
        { 
            data->current.is_day = (bool)is_day->valueint;
        }
    }

    cJSON *hourly = cJSON_GetObjectItem(root, "hourly");
    if(cJSON_IsObject(hourly))
    {
        cJSON* times = cJSON_GetObjectItemCaseSensitive(hourly, "time");
        if(cJSON_IsArray(times))
        {
            int count = cJSON_GetArraySize(times);
            for(int i = 0; i < count && i < WEATHER_HOURLY_COUNT; i++)
            {
                cJSON* value = cJSON_GetArrayItem(times, i);
                if(cJSON_IsString(value))
                {
                    snprintf(data->hourly.time[i], sizeof(data->hourly.time[i]), "%s", value->valuestring);
                }
            }
        }

        cJSON* temperatures = cJSON_GetObjectItemCaseSensitive(hourly, "temperature_2m");
        if(cJSON_IsArray(temperatures))
        {
            int count = cJSON_GetArraySize(temperatures);

            for(int i = 0; i < count && i < WEATHER_HOURLY_COUNT; i++)
            {
                cJSON *value = cJSON_GetArrayItem(temperatures, i);
                if(cJSON_IsNumber(value))
                {
                    data->hourly.temperature[i] = (float)value->valuedouble;
                }
            }
        }

        cJSON* apparent_temperatures = cJSON_GetObjectItemCaseSensitive(hourly, "apparent_temperature");
        if(cJSON_IsArray(apparent_temperatures))
        {
            int count = cJSON_GetArraySize(apparent_temperatures);
            for(int i = 0; i < count && i < WEATHER_HOURLY_COUNT; i++)
            {
                cJSON* value = cJSON_GetArrayItem(apparent_temperatures, i);
                if(cJSON_IsNumber(value))
                {
                    data->hourly.feels_like[i] = (float)value->valuedouble;
                }
            }
        }

        cJSON* relative_humidity = cJSON_GetObjectItemCaseSensitive(hourly, "relative_humidity_2m");
        if(cJSON_IsArray(relative_humidity))
        {
            int count = cJSON_GetArraySize(relative_humidity);

            for(int i = 0; i < count && i < WEATHER_HOURLY_COUNT; i++)
            {
                cJSON* value = cJSON_GetArrayItem(relative_humidity, i);
                if(cJSON_IsNumber(value))
                {
                    data->hourly.humidity[i] = (uint8_t)value->valueint;
                }
            }
        }


        cJSON* precipitation_probability = cJSON_GetObjectItemCaseSensitive(hourly, "precipitation_probability");
        if(cJSON_IsArray(precipitation_probability))
        {
            int count = cJSON_GetArraySize(precipitation_probability);
        for(int i = 0; i < count && i < WEATHER_HOURLY_COUNT; i++)
        {
            cJSON* value = cJSON_GetArrayItem(precipitation_probability, i);
            if(cJSON_IsNumber(value))
            {
                data->hourly.precipitation_probability[i] = (uint8_t)value->valueint;
            }
        }

        }

        cJSON* preciptiation = cJSON_GetObjectItemCaseSensitive(hourly, "precipitation");
        if(cJSON_IsArray(preciptiation))
        {
        int count = cJSON_GetArraySize(preciptiation);
        for(int i = 0; i < count && i < WEATHER_HOURLY_COUNT; i++)
        {
            cJSON* value = cJSON_GetArrayItem(preciptiation, i);
            if(cJSON_IsNumber(value))
            {
                data->hourly.precipitation[i] = (float)value->valuedouble;
            }
        }
        }

        cJSON* snow_depth = cJSON_GetObjectItemCaseSensitive(hourly, "snow_depth");
        if(cJSON_IsArray(snow_depth))
        {
            int count = cJSON_GetArraySize(snow_depth);
            for(int i = 0; i < count && i < WEATHER_HOURLY_COUNT; i++)
            {
                cJSON* value = cJSON_GetArrayItem(snow_depth, i);
                if(cJSON_IsNumber(value))
                {
                    data->hourly.snow_depth[i] = (float)value->valuedouble;
                }
            }
        }

        cJSON* weather_code = cJSON_GetObjectItemCaseSensitive(hourly, "weather_code");
        if(cJSON_IsArray(weather_code))
        {
            int count = cJSON_GetArraySize(weather_code);
            for(int i = 0; i < count && i < WEATHER_HOURLY_COUNT; i++)
            {
                cJSON* value = cJSON_GetArrayItem(weather_code, i);
                if(cJSON_IsNumber(value))
                {
                    data->hourly.weather_code[i] = (uint8_t)value->valueint;
                }
            }
        }

        cJSON* visibility = cJSON_GetObjectItemCaseSensitive(hourly, "visibility");
        if(cJSON_IsArray(visibility))
        {
            int count = cJSON_GetArraySize(visibility);
            for(int i = 0; i < count && i < WEATHER_HOURLY_COUNT; i++)
            {
                cJSON* value = cJSON_GetArrayItem(visibility, i);
                if(cJSON_IsNumber(value))
                {
                    data->hourly.visibility[i] = (float)value->valuedouble;
                }
            }
        }

        cJSON* wind_speed_10m = cJSON_GetObjectItemCaseSensitive(hourly, "wind_speed_10m");
        if(cJSON_IsArray(wind_speed_10m))
        {
            int count = cJSON_GetArraySize(wind_speed_10m);
            for(int i = 0; i < count && i < WEATHER_HOURLY_COUNT; i++)
            {
                cJSON* value = cJSON_GetArrayItem(wind_speed_10m, i);
                if(cJSON_IsNumber(value))
                {
                    data->hourly.wind_speed[i] = (float)value->valuedouble;
                }
            }
        }

        cJSON* wind_direction_10m = cJSON_GetObjectItemCaseSensitive(hourly, "wind_direction_10m");
        if(cJSON_IsArray(wind_direction_10m))
        {
            int count = cJSON_GetArraySize(wind_direction_10m);
            for(int i = 0; i < count && i < WEATHER_HOURLY_COUNT; i++)
            {
                cJSON* value = cJSON_GetArrayItem(wind_direction_10m, i);
                if(cJSON_IsNumber(value))
                {
                    data->hourly.wind_direction[i] = (uint16_t)value->valueint;
                }
            }
        }

        cJSON* wind_gusts_10m = cJSON_GetObjectItemCaseSensitive(hourly, "wind_gusts_10m");
        if(cJSON_IsArray(wind_gusts_10m))
        {
            int count = cJSON_GetArraySize(wind_direction_10m);
            for(int i = 0; i < count && i < WEATHER_HOURLY_COUNT; i++)
            {
                cJSON* value = cJSON_GetArrayItem(wind_gusts_10m, i);
                if(cJSON_IsNumber(value))
                {
                    data->hourly.wind_direction[i] = (float)value->valuedouble;
                }
            }
        }

    }

    cJSON *daily = cJSON_GetObjectItem(root, "daily");
    if(cJSON_IsObject(daily))
    {
        cJSON* dates = cJSON_GetObjectItemCaseSensitive(daily, "time");
        if(cJSON_IsArray(dates))
        {
            int count = cJSON_GetArraySize(dates);
            for(int i = 0; i < count && i < WEATHER_DAILY_COUNT; i++)
            {
                cJSON* value = cJSON_GetArrayItem(dates, i);
                if(cJSON_IsString(value))
                {
                    snprintf(data->daily.date[i], sizeof(data->daily.date), "%s", value->valuestring);
                }
            }
        }

        cJSON* daylight_duration = cJSON_GetObjectItemCaseSensitive(daily, "daylight_duration");
        if(cJSON_IsArray(daylight_duration))
        {
            int count = cJSON_GetArraySize(daylight_duration);
            for(int i = 0; i < count && i < WEATHER_DAILY_COUNT; i++)
            {
                cJSON* value = cJSON_GetArrayItem(daylight_duration, i);
                if(cJSON_IsNumber(value))
                {
                    data->daily.daylight_duration[i] = (float)value->valuedouble;
                }
            }
        }

        cJSON* weather_code = cJSON_GetObjectItemCaseSensitive(daily, "weather_code");
        if(cJSON_IsArray(weather_code))
        {
            int count = cJSON_GetArraySize(weather_code);
            for(int i = 0; i < count && i < WEATHER_DAILY_COUNT; i++)
            {
                cJSON* value = cJSON_GetArrayItem(weather_code, i);
                if(cJSON_IsNumber(value))
                {
                    data->daily.weather_code[i] = (uint8_t)value->valueint;
                }
            }
        }

        cJSON* sunrise = cJSON_GetObjectItemCaseSensitive(daily, "sunrise");
        if(cJSON_IsArray(sunrise))
        {
            int count = cJSON_GetArraySize(sunrise);
            for(int i = 0; i < count && i < WEATHER_DAILY_COUNT; i++)
            {
                cJSON* value = cJSON_GetArrayItem(dates, i);
                if(cJSON_IsString(value))
                {
                    snprintf(data->daily.sunrise[i], sizeof(data->daily.sunrise[i]), "%s", value->valuestring);
                }
            }
        }

        cJSON* sunset = cJSON_GetObjectItemCaseSensitive(daily, "sunset");
        if(cJSON_IsArray(sunset))
        {
            int count = cJSON_GetArraySize(sunset);
            for(int i = 0; i < count && i < WEATHER_DAILY_COUNT; i++)
            {
                cJSON* value = cJSON_GetArrayItem(dates, i);
                if(cJSON_IsString(value))
                {
                    snprintf(data->daily.sunset[i], sizeof(data->daily.sunset[i]), "%s", value->valuestring);
                }
            }
        }

    }
}