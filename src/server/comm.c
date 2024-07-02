/**************************************************\
 * @file comm.c                         
 *
 * @brief Implementation of communication functions
\**************************************************/

#include "comm.h"

ISR(USART0_RX_vect) {
    uint8_t receivedByte = UDR0;
    
    g_buf[writeIndex++] = receivedByte;

    if (writeIndex == sizeof(ui_t)) {
        options = *(ui_t*)g_buf;
        memset(g_buf, 0, sizeof(ui_t));
        
        writeIndex = 0;
    }
}

void sample(ui_t* options)
{
    if (options->mode == 0)
    {
        sample_cont(options);
    }
    else if (options->mode == 1)
    {
        sample_buf(options);
    }
    g_time_sent = (g_time_sent + 1) % MAX_TIME;
}

void sample_cont(ui_t* options)
{
    uint16_t adc_value;

    for (uint8_t i = 0; i < 16; i++)
    {
        if (options->channel_msk & (1 << i))
        {
            adc_value = adc_read(i);
            packet_t packet = {
                .timestamp = g_time_sent,
                .value = adc_value,        
                .channel = i};

            send_packet(&packet);
        }
    }
}

void sample_buf(ui_t* options)
{
    uint16_t adc_value;

    for (uint8_t i = 0; i < 16; i++)
    {
        if (options->channel_msk & (1 << i))
        {
            adc_value = adc_read(i);
            packet_t packet = {
                .timestamp = g_time_sent,
                .value = adc_value,        
                .channel = i};

            pkt_buff[pkt_buff_index % BULK_SIZE] = packet;
            pkt_buff_index++;
        }

        if (pkt_buff_index == BULK_SIZE)
        {
            pkt_buff_index = 0;

            for (uint8_t i = 0; i < BULK_SIZE; i++)
            {
                send_packet(&pkt_buff[i]);
            }
        }
    }

}

void send_packet(packet_t* packet)
{
    uint8_t* p = (uint8_t*) packet;

    for(uint8_t i = 0; i < sizeof(packet_t); ++i)
    {
        UART_putChar(*p);
        ++p;
    }
} 