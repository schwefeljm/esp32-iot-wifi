#include "globals.h"
#include "interrupt.h"
#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/queue.h"
#include "esp_sleep.h"
#include "esp_log.h"
#include "log.h"
#include "mqtt.h"


/*******************************************************

 * Need to rework all of this to make it more 
 * generically confirurable.
 * Right now, just making it work.


*******************************************************/

void gpio_isr_handler(void* arg)
{

    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(interputQueue, &gpio_num, NULL);
}



void LED_Control_Task(void *params)
{
    int pinNumber = 0;

    while (true)
    {
        if (xQueueReceive(interputQueue, &pinNumber, portMAX_DELAY))
        {
            //printf("GPIO %d was pressed %d times. The state is %d\n", pinNumber, count++, gpio_get_level(interruptPinMap[0]));
            gpio_set_level(LED_PIN, !gpio_get_level(interruptPinMap[0]));

            if(!gpio_get_level(interruptPinMap[0]))
            {
                ESP_LOGI(TAG, "Switch is open");
                send_mqtt(NULL, "On");

            }
            else
            {
                ESP_LOGI(TAG, "Switch is closed");
                send_mqtt(NULL, "Off");

            }
        }
    }
}


void config_interrupts(void) 
{

/////////////////////////////////////////////////////////////////////////////



    ESP_ERROR_CHECK(gpio_set_intr_type(interruptPinMap[0], GPIO_INTR_ANYEDGE));
    interputQueue = xQueueCreate(10, sizeof(int));

    BaseType_t xReturned = xTaskCreate(LED_Control_Task, "LED_Control", 4096, NULL, 1, NULL);
    if(xReturned == pdPASS)
    {
        printf("LED Control Task created.\n");
    }
    
    gpio_install_isr_service(ESP_INTR_FLAG_LEVEL1);

    gpio_isr_handler_add(interruptPinMap[0], gpio_isr_handler, (void *)interruptPinMap[0]);

    if(esp_sleep_is_valid_wakeup_gpio(interruptPinMap[0]))
    {
        ESP_LOGI(TAG, "Hall Effect Sensor GPIO is valid");
    }

    printf("Minimum free heap size: %"PRIu32" bytes\n", esp_get_minimum_free_heap_size());

////////////////////////////////////////////////////////////////////////////


}
