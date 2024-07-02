/**************************************************\
 * @file sample.h                         
 *
 * @brief Header for sampling functions
\**************************************************/

#pragma once
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "plot.h"

struct ui_s;
typedef struct ui_s ui_t;

/**************************************************\
 * @brief Represents a packet of data to receive
 * 
 * @param timestamp The time the data was sampled
 * @param value The value read from the channel
 * @param channel The channel the data was read from
\**************************************************/
typedef struct __attribute__((packed)) packet_s
{
    uint16_t timestamp;
    uint16_t value;
    uint8_t channel;
} packet_t;

/**************************************************\
 * @brief Ensures the first packet is received
 * 
 * @param options The options to sample with
 * @return 0 if successful, 1 if failed
\**************************************************/
uint8_t init_sample(ui_t* options);

/**************************************************\
 * @brief Handles the received data and plots it
 * 
 * @param options The options to sample with
\**************************************************/
void sample(ui_t* options);

/**************************************************\
 * @brief Sends the settings to the server
 * 
 * @param options The options to send
\**************************************************/
void send_settings(ui_t* options);

/**************************************************\
 * @brief Reveives a packet from the server
 * 
 * @param fd The file descriptor to read from
 * @param packet The packet to read into
\**************************************************/
void receive_packet(int fd, packet_t* packet);

/**************************************************\
 * @brief Sends the settings to the server to stop
 * 
 * @param options The options to send
\**************************************************/
void send_stop(ui_t* options);

/**************************************************\
 * @brief Clears the serial buffer
 * 
 * @param options The options used to receive
\**************************************************/
void recv_all(ui_t* options);

#include "ui.h"