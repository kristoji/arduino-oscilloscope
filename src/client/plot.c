#include "plot.h"

FILE *gnuplotPipe = NULL;

void init_gnuplot() { 
    gnuplotPipe = popen("gnuplot -persistent", "w");

    if (gnuplotPipe == NULL) {
        fprintf(stderr, "Error: Cannot open Gnuplot pipe\n");
    } else {
        fprintf(gnuplotPipe, "set title 'Oscilloscope'\n");
        fprintf(gnuplotPipe, "set xlabel 'Time'\n");
        fprintf(gnuplotPipe, "set ylabel 'Value'\n");
        fprintf(gnuplotPipe, "set yrange [0:1024]\n");
    }
}

void close_gnuplot() {
    if (gnuplotPipe != NULL) {
        pclose(gnuplotPipe);
        gnuplotPipe = NULL;
    }
}

void plot_with_gnuplot(uint16_t values[16][100]) {
    if (gnuplotPipe == NULL) {
        fprintf(stderr, "Error: Gnuplot pipe is not open\n");
        return;
    }

    // Write the data to separate temporary files for each channel
    for (int ch = 0; ch < 16; ++ch) {
        char filename[20];
        sprintf(filename, "data/data_%d.temp", ch);
        FILE *tempDataFile = fopen(filename, "w");

        if (tempDataFile == NULL) {
            fprintf(stderr, "Error: Cannot open temporary data file %s\n", filename);
            return;
        }

        for (int j = 0; j < 100; ++j) {
            fprintf(tempDataFile, "%d %d\n", j, values[ch][j]);
        }

        fclose(tempDataFile);
    }

    // Plot the data with Gnuplot
    fprintf(gnuplotPipe, "plot ");
    for (int ch = 0; ch < 16; ++ch) {
        char filename[20];
        sprintf(filename, "data/data_%d.temp", ch);
        fprintf(gnuplotPipe, "'%s' using 1:2 with lines title 'Channel %d'", filename, ch);
        if (ch < 15) {
            fprintf(gnuplotPipe, ", ");
        }
    }

    fprintf(gnuplotPipe, "\n");
    fflush(gnuplotPipe);
}

// int main() {
//     uint16_t values[16][100];

//     init_gnuplot();

//     for (int k = 0; k < 10; k++) {
//         for (int j = 0; j < 16; ++j) {
//             for (int i = 0; i < 100; ++i) {
//                 values[j][i] = 100 * k + 10 * j + i;
//             }
//         }
//         printf("Generated random data\n");
//         fflush(stdout);
//         plot_with_gnuplot(values);
//         sleep(1);
//     }

//     close_gnuplot();

//     return 0;
// }
