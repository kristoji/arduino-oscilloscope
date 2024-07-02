/**************************************************\
 * @file comm.h                         
 *
 * @brief Header for communication functions
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

#define MAX_FREQ 20
#define BULK_SIZE 10
#define MAX_TIME 100

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
 * @brief Represents a packet of data to send
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
 * @brief Buffer to read the options from the serial
\**************************************************/
volatile uint8_t g_buf[sizeof(ui_t)];
volatile uint8_t writeIndex;
volatile uint8_t recv;

/**************************************************\
 * @brief The options got from the user
\**************************************************/
volatile ui_t options;

/**************************************************\
 * @brief The global time of the system
\**************************************************/
volatile uint8_t g_time;

/**************************************************\
 * @brief The timestamp to send with the packet
\**************************************************/
volatile uint8_t g_time_sent;

/**************************************************\
 * @brief The packet buffer for buffered mode
\**************************************************/
volatile packet_t pkt_buff[BULK_SIZE];
volatile uint8_t pkt_buff_index;

/**************************************************\
 * @brief Reads the options from the serial
\**************************************************/
ISR(USART0_RX_vect);

/**************************************************\
 * @brief Starts a sample based on the option mode
 * 
 * @param options The options to sample with
\**************************************************/
void sample(ui_t* options);

/**************************************************\
 * @brief Samples the channels and sends the data
 * 
 * @param options The options to sample with
\**************************************************/
void sample_cont(ui_t* options);

/**************************************************\
 * @brief Samples the channels and stores the data
 *      sending it in bulk when the buffer is full
 * 
 * @param options The options to sample with
\**************************************************/
void sample_buf(ui_t* options);

/**************************************************\
 * @brief Sends a packet over the serial
 * 
 * @param packet The packet to send
\**************************************************/
void send_packet(packet_t* packet);

