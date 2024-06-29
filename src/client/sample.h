#pragma once
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

struct ui_s;
typedef struct ui_s ui_t;

void sample_buf(ui_t* options);
void sample_cont(ui_t* options);

#include "ui.h"