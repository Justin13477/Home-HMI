#include "datatypes.h"

int8_t tag_map_insert(tag_map_t *map, const char* tag, tag_handler_t handler);

tag_handler_t tag_map_lookup(tag_map_t *map, const char* tag);

uint8_t dispatch_tag(tag_map_t *map, app_data_t *data, const char* tag, const char* payload, uint32_t length);

