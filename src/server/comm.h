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

typedef struct ui_s {
    int32_t  fd;
    uint16_t channel_msk;
    uint8_t  frequency;
    uint8_t  mode;
} ui_t;

typedef struct __attribute__((packed)) packet_s
{
    uint16_t timestamp;
    uint16_t value;
    uint8_t channel;
} packet_t;


volatile uint8_t g_buf[sizeof(ui_t)];
volatile uint8_t writeIndex;
volatile uint8_t recv;
volatile ui_t options;
volatile uint8_t g_time;


ISR(USART0_RX_vect);

void handle_settings(ui_t* options);

void sample(ui_t* options);
void sample_cont(ui_t* options);
void sample_buf(ui_t* options);

void send_packet(packet_t* packet);

