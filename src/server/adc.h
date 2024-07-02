/**************************************************\
 * @file adc.h                          
 *
 * @brief Header for the ADC functions
\**************************************************/



#pragma once
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/iom2560.h>        // to avoid error in the IDE
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>


/**************************************************\
 * @brief Initialize the ADC
\**************************************************/
void adc_init();


/**************************************************\
 * @brief Reads the analog value of the channel
 * 
 * @param chnl The channel to read from (0-15)
 * @return The analog value of the channel
\**************************************************/
uint16_t adc_read(uint8_t chnl);