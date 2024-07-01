#include "sample.h"

void sample_cont(ui_t* options)
{
    printf("----------------------------\n");
    printf("Starting continuous sampling:\n");

    uint16_t values[16][100] = {0};
    uint16_t prev_timestamp = -1;

    init_gnuplot();

    while (1) 
    {
        int read_bytes = 0;
        packet_t packet;
        uint8_t buf[sizeof(packet_t)];

        do  
        {
            int n = read(options->fd, buf + read_bytes, sizeof(packet_t));
            read_bytes += n;
        } while (read_bytes < sizeof(packet_t));

        memcpy(&packet, buf, sizeof(packet_t));

        if (packet.timestamp != prev_timestamp)
        {
            plot_with_gnuplot(values);
            prev_timestamp = packet.timestamp;
        }

        values[packet.channel][packet.timestamp%100] = packet.value;
    }

    close_gnuplot();
} 

void sample_buf(ui_t* options)
{
    printf("Sample buffered not implemented yet\n");
}

void send_settings(ui_t* options)
{
    int n = write(options->fd, options, sizeof(ui_t));
    printf("Sent %d bytes of %ld\n", n, sizeof(ui_t));
}