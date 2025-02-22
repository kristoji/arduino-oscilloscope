/**************************************************\
 * @file server.h       
 *
 * @brief Header for the Oscilloscope main 
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
#include "adc.h"
#include "comm.h"
#include "time.h"
