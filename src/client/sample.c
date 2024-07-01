#include "sample.h"

void sample(ui_t* options)
{
    printf("----------------------------\n");
    printf("Starting sampling:\n");

    uint16_t values[16][100] = {0};
    uint16_t prev_timestamp = -1;

    init_gnuplot();

    while (1) 
    {
        packet_t packet;
        
        receive_packet(options->fd, &packet);

        if (packet.timestamp != prev_timestamp)
        {
            plot_with_gnuplot(values);
            prev_timestamp = packet.timestamp;
        }

        values[packet.channel][packet.timestamp%100] = packet.value;
    }

    close_gnuplot();
} 

void send_settings(ui_t* options)
{
    int n = write(options->fd, options, sizeof(ui_t));
    printf("Sent %d bytes of %ld\n", n, sizeof(ui_t));
}

void receive_packet(int fd, packet_t* packet)
{
    uint8_t buf[sizeof(packet_t)];
    int read_bytes = 0;

    do  
    {
        int n = read(fd, buf + read_bytes, sizeof(packet_t) - read_bytes);
        read_bytes += n;
    } while (read_bytes < sizeof(packet_t));

    memcpy(packet, buf, sizeof(packet_t));
}