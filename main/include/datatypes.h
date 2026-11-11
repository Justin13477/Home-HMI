#ifndef DATATYPES_H
#define DATATYPES_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#define TAG_MAP_CAPACITY 32

typedef struct {
    const char *topic;

    const char *payload;
    uint32_t payload_len;
} mqtt_q_message_t; // for passing through queue

typedef enum 
{
    SENSOR_ONLINE,
    SENSOR_OFFLINE,
    SENSOR_ERROR
} sensor_state_t;

typedef struct {
    float temp;
    float hum;
    sensor_state_t sht41_state;

    float lux;
    sensor_state_t veml7700_state;

} room_data_t; // data for each room

typedef struct {
    room_data_t *bedroom;
} app_data_t; // all app data

typedef struct 
{
    char wifi_ssid[32];
    char wifi_pass[64];
    char mqtt_address[32];
} settings_t;


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


#endif
