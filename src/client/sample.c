/**************************************************\
 * @file sample.c                         
 *
 * @brief Implementation of functions to get samples
\**************************************************/

#include "sample.h"

uint8_t init_sample(ui_t* options)
{
    printf("----------------------------\n");
    printf("Starting sampling:\n");

    packet_t packet;
    uint8_t fail_cnt = 0;
    do {
        receive_packet(options->fd, &packet);
        // printf("received T: %d, C: %d, V: %d\n", packet.timestamp, packet.channel, packet.value);
        fail_cnt++;
    } while(packet.timestamp != 0 && fail_cnt < 10);

    if (fail_cnt == 10)
    {
        printf("Failed to receive first packet\n");
        send_stop(options);
        return 1;
    }

    return 0;
}

void sample(ui_t* options)
{
    if (init_sample(options))
    {
        return;
    }

    packet_t packet;
    int16_t values[16][100] = {-10};
    uint16_t prev_timestamp = -1;
    init_gnuplot();

    while (1) 
    {
        receive_packet(options->fd, &packet);
        // printf("received T: %d, C: %d, V: %d\n", packet.timestamp, packet.channel, packet.value);

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
    uint8_t sent_bytes = 0;
    uint8_t* ptr = (uint8_t*) options;
    
    do
    {
        int n = write(options->fd, ptr + sent_bytes, sizeof(ui_t) - sent_bytes);
        sent_bytes += n;
    } while (sent_bytes < sizeof(ui_t));
    

    printf("Settings sent\n");
}

void send_stop(ui_t* options)
{
    uint8_t mode = options->mode;
    options->mode = 2;
    send_settings(options);
    options->mode = mode;

    recv_all(options);
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

void recv_all(ui_t* options)
{
    uint8_t buf[100];
    int n;
    do
    {
        n = read(options->fd, buf, 100);
    } while (n > 0);
}