#pragma once
#include <stdio.h>
#include <stdint.h>
#include "sample.h"

#define MAX_FREQ 20

typedef struct ui_s {
    int fd;
    uint16_t channel_msk;
    uint8_t frequency;
    uint8_t mode;
} ui_t;

int8_t display_menu(ui_t* options);
void set_channels(ui_t* options);
void set_freq(ui_t* options);
void set_mode(ui_t* options);

uint8_t ui_menu(ui_t* options);