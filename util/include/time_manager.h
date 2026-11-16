#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <time.h>
#include <stdbool.h>

void time_manager_init(void);

bool time_manager_is_synced(void);

bool time_manager_get_time(struct tm* time_info);

#endif