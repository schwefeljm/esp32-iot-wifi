#ifndef interrupt
    #define interrupt

    void gpio_isr_handler(void* arg);
    void LED_Control_Task(void *params);
    void config_interrupts(void);



#endif