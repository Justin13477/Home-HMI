#include "system_init.h"
#include "main.h"
#include "ui_styles.h"


/*---------------------------------------------------------------
 * Power / handle storage
 *--------------------------------------------------------------*/

/* LDO channels that power the LCD and the IO domain. */
static esp_ldo_channel_handle_t ldo3 = NULL;
static esp_ldo_channel_handle_t ldo4 = NULL;


    /* Dashboard layout (AI Suggestion)
SCREEN
│
└── MAIN CONTAINER (Flex: Row)
    │
    ├── SIDEBAR (Flex: Column)
    │   ├── Home Button
    │   ├── Rooms Button
    │   ├── Sensors Button
    │   ├── Lighting Button
    │   └── Settings Button
    │
    └── CONTENT CONTAINER (Flex: Column)
        │
        ├── HEADER (Flex: Row)
        │   ├── Page Title
        │   ├── Room Selector
        │   └── Status Indicator
        │
        └── DASHBOARD (Grid: 2 Columns × 2 Rows)
            ├── Temperature Card
            ├── Humidity Card
            ├── Lighting Card
            └── Air Quality Card

*/
    


/*---------------------------------------------------------------
 * Initialisation helpers
 *--------------------------------------------------------------*/

/**
 * @brief Halt forever and print the failing module name every second.
 * @param module_name Name of the failing module.
 * @param err         Error code returned by the module.
 */
static void init_fail_handler(const char *module_name, esp_err_t err)
{
    while (1) {
        MAIN_ERROR("[%s] init failed: %s", module_name, esp_err_to_name(err));
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/**
 * @brief Bring up LDO power, I2C, touch, LCD, backlight and LED GPIO.
 *
 * Order matters: LDO3/LDO4 power the panel; I2C must exist before
 * the touch driver; the LCD + LVGL must be ready before the
 * backlight is enabled; finally the LED GPIO is configured off.
 */
void system_init(void)
{
    esp_err_t err = ESP_OK;

    /* LDO3 = 2.5 V (IO domain), LDO4 = 3.3 V (panel analogue). */
    esp_ldo_channel_config_t ldo3_cof = {
        .chan_id = 3,
        .voltage_mv = 2500,
    };
    err = esp_ldo_acquire_channel(&ldo3_cof, &ldo3);
    if (err != ESP_OK) {
        init_fail_handler("ldo3", err);
    }

    esp_ldo_channel_config_t ldo4_cof = {
        .chan_id = 4,
        .voltage_mv = 3300,
    };
    err = esp_ldo_acquire_channel(&ldo4_cof, &ldo4);
    if (err != ESP_OK) {
        init_fail_handler("ldo4", err);
    }
    MAIN_INFO("LDO3 and LDO4 init success");

    /* I2C is required by the GT911 touch controller. */
    MAIN_INFO("Initializing I2C...");
    err = i2c_init();
    if (err != ESP_OK) {
        init_fail_handler("I2C", err);
    }
    MAIN_INFO("I2C init success");

    /* Touch panel (low-level GT911 driver). */
    MAIN_INFO("Initializing touch panel...");
    err = touch_init();
    if (err != ESP_OK) {
        init_fail_handler("Touch", err);
    }
    MAIN_INFO("Touch panel init success");

    /* LCD + LVGL must be ready before the backlight is turned on. */
    err = display_init();
    if (err != ESP_OK) {
        init_fail_handler("LCD", err);
    }
    MAIN_INFO("LCD init success");

    /* Full brightness. */
    err = set_lcd_blight(100);
    if (err != ESP_OK) {
        init_fail_handler("LCD Backlight", err);
    }
    MAIN_INFO("LCD backlight opened (brightness: 100)");

    /* LED GPIO starts off so the UI reflects the initial state. */
    MAIN_INFO("Initializing GPIO48 for LED...");
    err = gpio_extra_init();
    if (err != ESP_OK) {
        init_fail_handler("GPIO48", err);
    }
    gpio_extra_set_level(false);
    MAIN_INFO("LED initialized to OFF state");
    init_styles();

    wifi_init_sta();
    mqtt_manager_init("mqtt://192.168.0.129:1883");
    mqtt_manager_start();
}

/*---------------------------------------------------------------
 * Application entry point
 *--------------------------------------------------------------*/

/**
 * @brief Main application entry point.
 *
 * Powers up all hardware, lights the screen and builds the LED
 * control UI. After this returns the LVGL task keeps rendering
 * and dispatching touch events in the background.
 */