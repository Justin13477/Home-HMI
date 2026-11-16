#ifndef DATATYPES_H
#define DATATYPES_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#define TAG_MAP_CAPACITY 32

#define SENSOR_STATUS_OFFLINE   (1U << 1)
#define SENSOR_STATUS_ONLINE    (1U << 2)
#define SENSOR_STATUS_ERROR     (1U << 3)


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

typedef void (*ui_page_switcher_cb_t)(page_state_t state);


#endif
