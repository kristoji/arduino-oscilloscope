/**************************************************\
 * @file time.h                        
 *
 * @brief Header for the time functions
\**************************************************/

#pragma once
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/iom2560.h>        // to avoid error in the IDE
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "my_uart.h"
#include "comm.h"

/**************************************************\
 * @brief Flag to indicate if a timer interrupt occurred
\**************************************************/
volatile uint8_t timer_irq;

/**************************************************\
 * @brief Initialize the timer and some global variables
\**************************************************/
void time_init();

/**************************************************\
 * @brief Increments the system time
\**************************************************/
ISR(TIMER1_COMPA_vect);
