#pragma once
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

void init_gnuplot();
void close_gnuplot();
void plot_with_gnuplot(int16_t values[16][100]);