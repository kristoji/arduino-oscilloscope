/**************************************************\
 * @file time.c                         
 *
 * @brief Implements the functions to handle 
 *        the system time
\**************************************************/


#include "time.h"

void time_init()
{
    options.mode = 2;           // stop as default
    g_time = 0;
    timer_irq = 0;
    g_time_sent = 0;
    pkt_buff_index = 0;


    // Set CTC mode
    TCCR1B |= (1 << WGM12);
    
    // Set CS10 and CS12 bits for 1024 prescaler
    TCCR1B |= (1 << CS10);
    TCCR1B |= (1 << CS12);
    
    // Set TOP value 
    OCR1A = 15.624 * (1000 / MAX_FREQ);
    
    // Enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
}

ISR(TIMER1_COMPA_vect)
{
    if (options.mode != 2)
    {
        timer_irq = 1;
        g_time = (g_time + 1) % MAX_TIME;
    }
    else
    {
        g_time = 0;
        g_time_sent = 0;
    }
}