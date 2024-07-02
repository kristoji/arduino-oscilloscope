/**************************************************\
 * @file server.c                         
 *
 * @brief Contains the Oscilloscope main function
\**************************************************/

#include "server.h"

int main(void) {
    UART_init();
    adc_init();
    time_init();
    
    sei();
    
    while (1) 
    {
        if (timer_irq)
        {
            timer_irq = 0;
    
            if (g_time % (MAX_FREQ / options.frequency) == 0)
                sample(&options);
        }
        sleep_mode();        
    }
    
    return 0;
}