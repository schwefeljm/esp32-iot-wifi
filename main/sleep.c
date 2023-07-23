//#include "esp_check.h"
#include "esp_sleep.h"
#include "driver/gpio.h"
//#include "interrupt.h"
#include "globals.h"
#include "log.h"
#include "sleep.h"
#include "driver/uart.h"
#include "esp_timer.h"
//#include "esp_task_wdt.h"
#include <time.h>
//#include "esp_wifi.h"
#include "esp_check.h"
#include "driver/rtc_io.h"

#define GPIO_WAKEUP_NUM_1 0
#define GPIO_WAKEUP_NUM_2 1

#define SOC_PM_SUPPORT_EXT0_WAKEUP 1


//static struct timeval sleep_enter_time;

static void light_sleep_task(void *args);
static void example_wait_gpio_active(void);
static void example_wait_gpio_inactive(void);
static esp_err_t example_register_gpio_wakeup(void);


static void light_sleep_task(void *args)
{
    while (true) {
        printf("Entering light sleep\n");
        /* To make sure the complete line is printed before entering sleep mode,
         * need to wait until UART TX FIFO is empty:
         */
        uart_wait_tx_idle_polling(UART_NUM_0);
        uart_wait_tx_idle_polling(UART_NUM_1);

        /* Get timestamp before entering sleep */
        int64_t t_before_us = esp_timer_get_time();

        /* Enter sleep mode */
        esp_deep_sleep_start();

        /* Get timestamp after waking up from sleep */
        int64_t t_after_us = esp_timer_get_time();

        /* Determine wake up reason */
        const char* wakeup_reason;
        switch (esp_sleep_get_wakeup_cause()) {
            case ESP_SLEEP_WAKEUP_GPIO:
                wakeup_reason = "pin";
                break;
            default:
                wakeup_reason = "other";
                break;
        }
        printf("Returned from light sleep, reason: %s, t=%lld ms, slept for %lld ms\n",
                wakeup_reason, t_after_us / 1000, (t_after_us - t_before_us) / 1000);

        if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_GPIO) {
            /* Waiting for the gpio inactive, or the chip will continously trigger wakeup*/
            example_wait_gpio_inactive();
        }

    }
    vTaskDelete(NULL);
}


static void example_wait_gpio_inactive(void)
{
    printf("Waiting for GPIO%d to go high...\n", interruptPinMap[0]);
    while (gpio_get_level(interruptPinMap[0]) == ESP_SLEEP_WAKEUP_EXT1) {
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

static void example_wait_gpio_active(void)
{
    printf("Waiting for GPIO%d to go low...\n", interruptPinMap[1]);
    while (gpio_get_level(interruptPinMap[1]) == GPIO_WAKEUP_LEVEL_LOW) {
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}


static esp_err_t example_register_gpio_wakeup(void)
{
    /* Initialize GPIO */
    gpio_config_t config = {
            .pin_bit_mask = BIT64(GPIO_WAKEUP_NUM_1),
            .mode = GPIO_MODE_INPUT,
            .pull_down_en = true,
            .pull_up_en = false,
            .intr_type = GPIO_INTR_HIGH_LEVEL
    };
    ESP_RETURN_ON_ERROR(gpio_config(&config), TAG, "Initialize GPIO%d failed", GPIO_WAKEUP_NUM_1);

    /* Enable wake up from GPIO */
    ESP_RETURN_ON_ERROR(gpio_wakeup_enable(GPIO_WAKEUP_NUM_1, GPIO_WAKEUP_LEVEL_HIGH == 0 ? GPIO_INTR_LOW_LEVEL : GPIO_INTR_HIGH_LEVEL),
                        TAG, "Enable gpio wakeup failed");
    ESP_RETURN_ON_ERROR(esp_sleep_enable_gpio_wakeup(), TAG, "Configure gpio as wakeup source failed");

    /* Make sure the GPIO is inactive and it won't trigger wakeup immediately */
    example_wait_gpio_inactive();
    ESP_LOGI(TAG, "gpio wakeup source is ready");

    return ESP_OK;
}


static esp_err_t register_ext1_wakeup(void) 
{

    rtc_gpio_pulldown_en(GPIO_WAKEUP_NUM_1);
    return esp_sleep_enable_ext1_wakeup(BIT64(GPIO_WAKEUP_NUM_1), ESP_EXT1_WAKEUP_ANY_HIGH);

    //return ESP_OK;
}

esp_err_t set_gpio_wake_task()
{
//    esp_err_t ret = example_register_gpio_wakeup();
    esp_err_t ret = register_ext1_wakeup();

    if(ret == ESP_OK) 
    {
        xTaskCreate(light_sleep_task, "light_sleep_task", 4096, NULL, 6, NULL);
    }
    
    return ret;

}