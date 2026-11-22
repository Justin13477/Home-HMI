#include "weather_manager.h"

#include <stdio.h>
#include <string.h>

#include "esp_http_client.h"
#include "esp_crt_bundle.h"
#include "esp_log.h"

#define WEATHER_UPDATE_INTERVAL pdMS_TO_TICKS(30 * 60 * 1000)

#define WEATHER_URL "https://api.open-meteo.com/v1/forecast?latitude=37.14645&longitude=-94.463&daily=daylight_duration,sunrise,sunset,weather_code&hourly=temperature_2m,relative_humidity_2m,apparent_temperature,is_day,precipitation_probability,precipitation,snow_depth,weather_code,visibility,wind_speed_10m,wind_direction_10m,wind_gusts_10m&current=temperature_2m,is_day,weather_code,relative_humidity_2m,apparent_temperature&timezone=auto&wind_speed_unit=mph&temperature_unit=fahrenheit&precipitation_unit=inch&forecast_hours=24"

static const char* TAG = "WEATHER_MANAGER";
static esp_http_client_handle_t handle;
static int response_length = 0;
static char buffer[4096] = {0};

static weather_data_t weather_data = {0};

QueueHandle_t weather_queue = NULL;

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

void interpret_weather_code(uint8_t code, weather_code_build_t* weather_code_build, bool is_day)
{
    switch(code)
    {
        case WEATHER_CLEAR:
        {
            ESP_LOGI(TAG, "Interpretting weather code");
            snprintf(weather_code_build->label, sizeof(weather_code_build->label), "%s", "Clear Weather");

            if(is_day)
            {
                weather_code_build->image_data_48 = &clear_day_48;
                weather_code_build->image_data_128 = &clear_day_128;
            }
            else if(!is_day)
            {
                weather_code_build->image_data_48 = &clear_night_48;
                weather_code_build->image_data_128 = &clear_night_128;
            }
            break;
        }

        case WEATHER_MAINLY_CLEAR:
        {
            snprintf(weather_code_build->label, sizeof(weather_code_build->label), "%s", "Mainly Clear Weather");

            if(is_day)
            {
                weather_code_build->image_data_48 = &clear_day_48;
                weather_code_build->image_data_128 = &clear_day_128;
            }
            else if(!is_day)
            {
                weather_code_build->image_data_48 = &clear_night_48;
                weather_code_build->image_data_128 = &clear_night_128;
            }
            break;
        }

        case WEATHER_PARTLY_CLOUDY:
        {
            snprintf(weather_code_build->label, sizeof(weather_code_build->label), "%s", "Partly Cloudy");

            if(is_day)
            {
                weather_code_build->image_data_48 = &partly_cloudy_day_48;
                weather_code_build->image_data_128 = &partly_cloudy_day_128;
            }
            else if(!is_day)
            {
                weather_code_build->image_data_48 = &partly_cloudy_night_48;
                weather_code_build->image_data_128 = &partly_cloudy_night_128;
            }
            break;
        }

        case WEATHER_OVERCAST:
        {
            snprintf(weather_code_build->label, sizeof(weather_code_build->label), "%s", "Overcast");

            if(is_day)
            {
                weather_code_build->image_data_48 = &overcast_day_48;
                weather_code_build->image_data_128 = &overcast_day_128;
            }
            else if(!is_day)
            {
                weather_code_build->image_data_48 = &overcast_night_48;
                weather_code_build->image_data_128 = &overcast_night_128;
            }
            break;
        }

        case WEATHER_FOG:
        {
            snprintf(weather_code_build->label, sizeof(weather_code_build->label), "%s", "Fog");

            if(is_day)
            {
                weather_code_build->image_data_48 = &fog_48;
                weather_code_build->image_data_128 = &fog_128;
            }
            else if(!is_day)
            {
                weather_code_build->image_data_48 = &fog_48;
                weather_code_build->image_data_128 = &fog_128;
            }
            break;
        }

        case WEATHER_DRIZZLE_LIGHT:
        {
            snprintf(weather_code_build->label, sizeof(weather_code_build->label), "%s", "Light Drizzle");

            if(is_day)
            {
                weather_code_build->image_data_48 = &rain_48;
                weather_code_build->image_data_128 = &rain_128;
            }
            else if(!is_day)
            {
                weather_code_build->image_data_48 = &rain_48;
                weather_code_build->image_data_128 = &rain_128;
            }
            break;
        }

        case WEATHER_DRIZZLE_MODERATE:
        {
            snprintf(weather_code_build->label, sizeof(weather_code_build->label), "%s", "Moderate Drizzle");

            if(is_day)
            {
                weather_code_build->image_data_48 = &rain_48;
                weather_code_build->image_data_128 = &rain_128;
            }
            else if(!is_day)
            {
                weather_code_build->image_data_48 = &rain_48;
                weather_code_build->image_data_128 = &rain_128;
            }
            break;
        }

        case WEATHER_DRIZZLE_DENSE:
        {
            snprintf(weather_code_build->label, sizeof(weather_code_build->label), "%s", "Dense Drizzle");

            if(is_day)
            {
                weather_code_build->image_data_48 = &rain_48;
                weather_code_build->image_data_128 = &rain_128;
            }
            else if(!is_day)
            {
                weather_code_build->image_data_48 = &rain_48;
                weather_code_build->image_data_128 = &rain_128;
            }
            break;
        }

        case WEATHER_RAIN_LIGHT:
        {
            snprintf(weather_code_build->label, sizeof(weather_code_build->label), "%s", "Light Rain");

            if(is_day)
            {
                weather_code_build->image_data_48 = &rain_48;
                weather_code_build->image_data_128 = &rain_128;
            }
            else if(!is_day)
            {
                weather_code_build->image_data_48 = &rain_48;
                weather_code_build->image_data_128 = &rain_128;
            }
            break;
        }

        case WEATHER_RAIN_MODERATE:
        {
            snprintf(weather_code_build->label, sizeof(weather_code_build->label), "%s", "Moderate Rain");

            if(is_day)
            {
                weather_code_build->image_data_48 = &rain_48;
                weather_code_build->image_data_128 = &rain_128;
            }
            else if(!is_day)
            {
                weather_code_build->image_data_48 = &rain_48;
                weather_code_build->image_data_128 = &rain_128;
            }
            break;
        }

        case WEATHER_RAIN_HEAVY:
        {
            snprintf(weather_code_build->label, sizeof(weather_code_build->label), "%s", "Heavy Rain");

            if(is_day)
            {
                weather_code_build->image_data_48 = &rain_48;
                weather_code_build->image_data_128 = &rain_128;
            }
            else if(!is_day)
            {
                weather_code_build->image_data_48 = &rain_48;
                weather_code_build->image_data_128 = &rain_128;
            }
            break;
        }

        case WEATHER_SNOW_LIGHT:
        {
            snprintf(weather_code_build->label, sizeof(weather_code_build->label), "%s", "Light Snow");

            if(is_day)
            {
                weather_code_build->image_data_48 = &snow_48;
                weather_code_build->image_data_128 = &snow_128;
            }
            else if(!is_day)
            {
                weather_code_build->image_data_48 = &snow_48;
                weather_code_build->image_data_128 = &snow_128;
            }
            break;
        }

        case WEATHER_SNOW_MODERATE:
        {
            snprintf(weather_code_build->label, sizeof(weather_code_build->label), "%s", "Moderate Snow");

            if(is_day)
            {
                weather_code_build->image_data_48 = &snow_48;
                weather_code_build->image_data_128 = &snow_128;
            }
            else if(!is_day)
            {
                weather_code_build->image_data_48 = &snow_48;
                weather_code_build->image_data_128 = &snow_128;
            }
            break;
        }

        case WEATHER_SNOW_HEAVY:
        {
            snprintf(weather_code_build->label, sizeof(weather_code_build->label), "%s", "Heavy Snow");

            if(is_day)
            {
                weather_code_build->image_data_48 = &snow_48;
                weather_code_build->image_data_128 = &snow_128;
            }
            else if(!is_day)
            {
                weather_code_build->image_data_48 = &snow_48;
                weather_code_build->image_data_128 = &snow_128;
            }
            break;
        }

        case WEATHER_RAIN_SHOWERS_LIGHT:
        {
            snprintf(weather_code_build->label, sizeof(weather_code_build->label), "%s", "Light Rain Showers");

            if(is_day)
            {
                weather_code_build->image_data_48 = &rain_48;
                weather_code_build->image_data_128 = &rain_128;
            }
            else if(!is_day)
            {
                weather_code_build->image_data_48 = &rain_48;
                weather_code_build->image_data_128 = &rain_128;
            }
            break;
        }

        case WEATHER_RAIN_SHOWERS_MODERATE:
        {
            snprintf(weather_code_build->label, sizeof(weather_code_build->label), "%s", "Moderate Rain Showers");

            if(is_day)
            {
                weather_code_build->image_data_48 = &rain_48;
                weather_code_build->image_data_128 = &rain_128;
            }
            else if(!is_day)
            {
                weather_code_build->image_data_48 = &rain_48;
                weather_code_build->image_data_128 = &rain_128;
            }
            break;
        }

        case WEATHER_RAIN_SHOWERS_VIOLENT:
        {
            snprintf(weather_code_build->label, sizeof(weather_code_build->label), "%s", "Violent Rain Showers");

            if(is_day)
            {
                weather_code_build->image_data_48 = &rain_48;
                weather_code_build->image_data_128 = &rain_128;
            }
            else if(!is_day)
            {
                weather_code_build->image_data_48 = &rain_48;
                weather_code_build->image_data_128 = &rain_128;
            }
            break;
        }

        case WEATHER_THUNDERSTORM:
        {
            snprintf(weather_code_build->label, sizeof(weather_code_build->label), "%s", "Thunderstorms");

            if(is_day)
            {
                weather_code_build->image_data_48 = &thunderstorms_day_48;
                weather_code_build->image_data_128 = &thunderstorms_day_128;
            }
            else if(!is_day)
            {
                weather_code_build->image_data_48 = &thunderstorms_night_48;
                weather_code_build->image_data_128 = &thunderstorms_night_128;
            }
            break;
        }

        case WEATHER_THUNDERSTORM_HAIL_LIGHT:
        {
            snprintf(weather_code_build->label, sizeof(weather_code_build->label), "%s", "Thunderstorms w/ Light Hail");

            if(is_day)
            {
                weather_code_build->image_data_48 = &thunderstorms_day_48;
                weather_code_build->image_data_128 = &thunderstorms_day_128;
            }
            else if(!is_day)
            {
                weather_code_build->image_data_48 = &thunderstorms_night_48;
                weather_code_build->image_data_128 = &thunderstorms_night_128;
            }
            break;
        }

        case WEATHER_THUNDERSTORM_HAIL_HEAVY:
        {
            snprintf(weather_code_build->label, sizeof(weather_code_build->label), "%s", "Thunderstorms w/ Heavy Hail");

            if(is_day)
            {
                weather_code_build->image_data_48 = &extreme_thunderstorms_extreme_day_48;
                weather_code_build->image_data_128 = &extreme_thunderstorms_extreme_day_128;
            }
            else if(!is_day)
            {
                weather_code_build->image_data_48 = &thunderstorms_extreme_night_48;
                weather_code_build->image_data_128 = &thunderstorms_extreme_night_128;
            }
            break;
        }
    }
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
        if(cJSON_IsNumber(is_day) || cJSON_IsBool(is_day))
        { 
            data->current.is_day = is_day->valueint != 0;
        }

        cJSON* feels_like = cJSON_GetObjectItemCaseSensitive(current, "apparent_temperature");
        if(cJSON_IsNumber(feels_like))
        {
            data->current.feels_like = (float)feels_like->valuedouble;
        }
        cJSON* humidity = cJSON_GetObjectItemCaseSensitive(current, "relative_humidity_2m");
        if(cJSON_IsNumber(humidity))
        {
            data->current.humidity = (uint8_t)humidity->valueint;
        }

        cJSON* weather_code = cJSON_GetObjectItemCaseSensitive(current, "weather_code");
        if(cJSON_IsNumber(weather_code))
        {
            data->current.weather_code = (uint8_t)weather_code->valueint;
            interpret_weather_code(
                data->current.weather_code,
                &data->current.weather_code_build, 
                data->current.is_day);
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

        cJSON* hourly_is_day = cJSON_GetObjectItemCaseSensitive(hourly, "is_day");
        if(cJSON_IsArray(hourly_is_day))
        {
            int count = cJSON_GetArraySize(hourly_is_day);
            for(int i = 0; i < count && i < WEATHER_HOURLY_COUNT; i++)
            {
                cJSON* value = cJSON_GetArrayItem(hourly_is_day, i);
                if(cJSON_IsNumber(value) || cJSON_IsBool(value))
                {
                    data->hourly.is_day[i] = value->valueint != 0;
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
                
            interpret_weather_code(
                data->hourly.weather_code[i],
                &data->hourly.weather_code_build[i], 
                data->hourly.is_day[i]);
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
            int count = cJSON_GetArraySize(wind_gusts_10m);
            for(int i = 0; i < count && i < WEATHER_HOURLY_COUNT; i++)
            {
                cJSON* value = cJSON_GetArrayItem(wind_gusts_10m, i);
                if(cJSON_IsNumber(value))
                {
                    data->hourly.wind_gusts[i] = (float)value->valuedouble;
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
                    snprintf(data->daily.date[i], sizeof(data->daily.date[i]), "%s", value->valuestring);
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
            interpret_weather_code(
                data->daily.weather_code[i],
                &data->daily.weather_code_build[i], 
                true);
            }
        }

        cJSON* sunrise = cJSON_GetObjectItemCaseSensitive(daily, "sunrise");
        if(cJSON_IsArray(sunrise))
        {
            int count = cJSON_GetArraySize(sunrise);
            for(int i = 0; i < count && i < WEATHER_DAILY_COUNT; i++)
            {
                cJSON* value = cJSON_GetArrayItem(sunrise, i);
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
                cJSON* value = cJSON_GetArrayItem(sunset, i);
                if(cJSON_IsString(value))
                {
                    snprintf(data->daily.sunset[i], sizeof(data->daily.sunset[i]), "%s", value->valuestring);
                }
            }
        }

    }
    cJSON_Delete(root);
}

bool weather_manager_get_data(weather_data_t* data)
{
    ESP_ERROR_CHECK(esp_http_client_perform(handle));

    ESP_LOGI(TAG, "HTTP Status: %d", esp_http_client_get_status_code(handle));

    int64_t content_length = esp_http_client_get_content_length(handle);
    ESP_LOGI(TAG, "Response Length: %", PRId64, content_length);

    ESP_LOGI(TAG, "Response: %s", buffer);

    parse_weather_data(buffer, sizeof(buffer), data);

    esp_http_client_cleanup(handle);

    
    return weather_data.valid;
}

void weather_manager_task(void *args)
{
    (void)args;

    while(1)
    {
        vTaskDelay(WEATHER_UPDATE_INTERVAL);

        weather_manager_get_data(&weather_data);
        weather_data_t *weather_ptr = &weather_data;
        xQueueSend(weather_queue, &weather_ptr, portMAX_DELAY);

        
    }
}

void weather_manager_init()
{
    
    esp_http_client_config_t config = 
    {
        .url = WEATHER_URL, 
        .method = HTTP_METHOD_GET, 
        .crt_bundle_attach = esp_crt_bundle_attach, 
        .timeout_ms = 10000, 
        .event_handler = http_event_handler,

        .buffer_size = 4096,
        .buffer_size_tx = 2048,
        .max_authorization_retries = 1,
    };

    handle = esp_http_client_init(&config);
    
    

    weather_manager_get_data(&weather_data);
    weather_data_t* weather_ptr = &weather_data;
    xQueueSend(weather_queue, &weather_ptr, portMAX_DELAY);
    
}