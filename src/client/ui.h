/**************************************************\
 * @file ui.h
 *
 * @brief Header for user interface functions
\**************************************************/
#pragma once
#include <stdio.h>
#include <stdint.h>
#include "sample.h"

#define MAX_FREQ 20

/**************************************************\
 * @brief Represents the options sent by the user
 * 
 * @param fd The file descriptor of the serial
 * @param channel_msk The channels to sample 
 * @param frequency The frequency to sample at
 * @param mode Continuous, Buffered, or Stop
\**************************************************/
typedef struct ui_s {
    int32_t  fd;
    uint16_t channel_msk;
    uint8_t  frequency;
    uint8_t  mode;
} ui_t;


/**************************************************\
 * @brief Displays the menu
 * 
 * @param options The options to display
 * @return The option selected
\**************************************************/
int8_t display_menu(ui_t* options);

/**************************************************\
 * @brief Sets the channels to sample
 * 
 * @param options The options to set
\**************************************************/
void set_channels(ui_t* options);

/**************************************************\
 * @brief Sets the frequency to sample at
 * 
 * @param options The options to set
\**************************************************/
void set_freq(ui_t* options);

/**************************************************\
 * @brief Sets the mode to sample
 * 
 * @param options The options to set
\**************************************************/
void set_mode(ui_t* options);

/**************************************************\
 * @brief Handles the user choice from the menu
 * 
 * @param options The options to set
 * @return If the user wants to continue
\**************************************************/
uint8_t ui_menu(ui_t* options);