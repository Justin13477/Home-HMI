#include "tag_map.h"
#include <stdio.h>
#include <string.h>

int8_t tag_map_insert(tag_map_t *map, const char* tag, tag_handler_t handler)
{
    uint32_t index = hash_tag(tag) % TAG_MAP_CAPACITY;

    for(int i = 0; i < TAG_MAP_CAPACITY; i++)
    {
        tag_entry_t *entry = 
            &map->entries[index];

        if(entry->tag == NULL)
        {
            entry->tag = tag;
            entry->handler = handler;
            return 1;
        }

        if(strcmp(entry->tag, tag) == 0)
        {
            entry->handler = handler;
            return 1;
        }
        index = (index + 1) % TAG_MAP_CAPACITY;
    }
    return 0;
}

tag_handler_t tag_map_lookup(tag_map_t *map, const char* tag)
{
    {
    uint32_t index = hash_tag(tag) % TAG_MAP_CAPACITY;

    for (size_t i = 0; i < TAG_MAP_CAPACITY; i++)
    {
        tag_entry_t *entry =
            &map->entries[index];

        // Reached an empty slot
        if (entry->tag == NULL)
            return NULL;

        // Found matching tag
        if (strcmp(entry->tag, tag) == 0)
            return entry->handler;

        // Continue probing
        index = (index + 1) % TAG_MAP_CAPACITY;
    }

    return NULL;
}
}

uint8_t dispatch_tag(tag_map_t *map, app_data_t *data, const char* tag, const char* payload, uint32_t length)
{
    tag_handler_t handler =
        tag_map_lookup(map, tag);

    if (handler == NULL)
        return 0;

    handler(data, payload, length);

    return 1;
}