#ifndef DATATYPES_H
#define DATATYPES_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include "lvgl.h"
#define TAG_MAP_CAPACITY 32

#define SENSOR_STATUS_OFFLINE   (1U << 1)
#define SENSOR_STATUS_ONLINE    (1U << 2)
#define SENSOR_STATUS_ERROR     (1U << 3)



#define WEATHER_HOURLY_COUNT 24
#define WEATHER_DAILY_COUNT 7

typedef struct 
{
    char label[32];
    const lv_image_dsc_t* image_data_48;
    const lv_image_dsc_t* image_data_128;

} weather_code_build_t;

typedef struct
{
    float temperature;
    bool is_day;

    float feels_like;
    uint8_t humidity;
    uint8_t weather_code;
    weather_code_build_t weather_code_build;

} weather_current_t;

typedef struct
{
    char time[WEATHER_HOURLY_COUNT][20];

    // Temperature
    float temperature[WEATHER_HOURLY_COUNT];
    float feels_like[WEATHER_HOURLY_COUNT];

    // Humidity
    uint8_t humidity[WEATHER_HOURLY_COUNT];

    // Wind
    float wind_speed[WEATHER_HOURLY_COUNT];
    uint16_t wind_direction[WEATHER_HOURLY_COUNT];
    float wind_gusts[WEATHER_HOURLY_COUNT];

    // Weather conditions
    uint8_t weather_code[WEATHER_HOURLY_COUNT];
    weather_code_build_t weather_code_build[WEATHER_HOURLY_COUNT];
    
    bool is_day[WEATHER_HOURLY_COUNT];

    // Precipitation
    uint8_t precipitation_probability[WEATHER_HOURLY_COUNT];
    float precipitation[WEATHER_HOURLY_COUNT];

    // Other conditions
    float snow_depth[WEATHER_HOURLY_COUNT];
    float visibility[WEATHER_HOURLY_COUNT];

} weather_hourly_t;


typedef struct
{
    char date[WEATHER_DAILY_COUNT][11];
    uint8_t weather_code[WEATHER_DAILY_COUNT];
    weather_code_build_t weather_code_build[WEATHER_DAILY_COUNT];

    float daylight_duration[WEATHER_DAILY_COUNT];

    char sunrise[WEATHER_DAILY_COUNT][20];
    char sunset[WEATHER_DAILY_COUNT][20];

} weather_daily_t;


typedef struct
{
    weather_current_t current;
    weather_hourly_t hourly;
    weather_daily_t daily;

    bool valid;

} weather_data_t;


typedef struct {
    const char *topic;

    const char *payload;
    uint32_t payload_len;
} mqtt_q_message_t; // for passing through queue

typedef struct {
    float temp;
    float hum;
    uint8_t sht41_state; // use bit manipulation for state

    float lux;
    uint8_t veml7700_state;

} sensor_data_t; // data for each room

typedef struct 
{
    char wifi_ssid[32];
    char wifi_pass[64];
    char mqtt_address[32];
} settings_t;

typedef struct { 
    char time[16];
    char date[16];
} dtime_t;
typedef struct {
    sensor_data_t *sensors;
    dtime_t *dtime;
    weather_data_t *weather_data;
} app_data_t; // all app data




typedef void (*tag_handler_t)(app_data_t *data, const char* payload, uint32_t length); // hanlder function pointer type

static inline void float_to_char(float num, char* buffer, size_t size)
    {
        snprintf(buffer, size, "%.2f", num);
    }

static inline uint32_t hash_tag(const char* tag) // simple FNV-1a hash
{
    uint32_t hash = 2166136261u;

    while(*tag)
    {
        hash ^= (uint8_t)*tag++;
        hash *= 16777619u;
    }
    return hash;
}

typedef struct {
    const char* tag;
    tag_handler_t handler;
} tag_entry_t; // tag entry

typedef struct {
    tag_entry_t entries[TAG_MAP_CAPACITY];
} tag_map_t; // tag map


typedef enum {
    PAGE_MAIN,
    PAGE_SETTINGS,
    PAGE_CLIMATE,
    PAGE_LIGHTING
} page_state_t;

typedef enum {
    SUBPAGE_CLIMATE, 
    SUBPAGE_WEATHER,
} subpage_state_t;

typedef void (*ui_page_switcher_cb_t)(page_state_t state);

typedef enum
{
    SIZE_32,
    SIZE_48,
    SIZE_96,
} icon_size_t;
typedef enum
{
    WEATHER_CLEAR = 0,
    WEATHER_MAINLY_CLEAR = 1,
    WEATHER_PARTLY_CLOUDY = 2,
    WEATHER_OVERCAST = 3,
    WEATHER_FOG = 45,
    WEATHER_DRIZZLE_LIGHT = 51,
    WEATHER_DRIZZLE_MODERATE = 53,
    WEATHER_DRIZZLE_DENSE = 55,
    WEATHER_RAIN_LIGHT = 61,
    WEATHER_RAIN_MODERATE = 63,
    WEATHER_RAIN_HEAVY = 65,
    WEATHER_SNOW_LIGHT = 71,
    WEATHER_SNOW_MODERATE = 73,
    WEATHER_SNOW_HEAVY = 75,
    WEATHER_RAIN_SHOWERS_LIGHT = 80,
    WEATHER_RAIN_SHOWERS_MODERATE = 81,
    WEATHER_RAIN_SHOWERS_VIOLENT = 82,
    WEATHER_THUNDERSTORM = 95,
    WEATHER_THUNDERSTORM_HAIL_LIGHT = 96,
    WEATHER_THUNDERSTORM_HAIL_HEAVY = 99

} weather_code_t;



#endif
