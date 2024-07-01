#pragma once
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "plot.h"

struct ui_s;
typedef struct ui_s ui_t;

typedef struct __attribute__((packed)) packet_s
{
    uint16_t timestamp;
    uint16_t value;
    uint8_t channel;
} packet_t;

void sample_buf(ui_t* options);
void sample_cont(ui_t* options);
void send_settings(ui_t* options);

#include "ui.h"