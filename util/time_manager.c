#include "time_manager.h"

#include <sys/time.h>
#include "esp_sntp.h"
#include "esp_log.h"

static const char* TAG = "TIME_MANAGER";

static bool time_synced = false;

static void time_sync_notification_cb(struct timeval* tv)
{
    ESP_LOGI(TAG, "Time synchronized");
    time_synced = true;
}

void time_manager_init(void)
{
    // Configure Central Time
    setenv("TZ", "CST6CDT,M3.2.0,M11.1.0", 1);
    tzset();

    // Configure SNTP
    esp_sntp_setoperatingmode(SNTP_OPMODE_POLL);

    esp_sntp_setservername(0, "pool.ntp.org");

    esp_sntp_set_time_sync_notification_cb(time_sync_notification_cb);

    esp_sntp_init();
}

bool time_manager_is_synced(void)
{
    return time_synced;
}

bool time_manager_get_time(struct tm* time_info)
{
    if (!time_synced || time_info == NULL)
        return false;

    time_t now;
    time(&now);

    localtime_r(&now, time_info);

    return true;
}