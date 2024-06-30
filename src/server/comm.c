#include "comm.h"

ISR(USART0_RX_vect) {
    uint8_t receivedByte = UDR0;
    
    g_buf[writeIndex++] = receivedByte;

    if (writeIndex == sizeof(ui_t)) {
        options = *(ui_t*)g_buf;
        writeIndex = 0;
        recv = 1;
    }
}

void handle_settings(ui_t* options)
{
    if (recv == 1) 
    {
        unsigned char buffer[1024];

        *options = *(ui_t*)g_buf;
        memset(g_buf, 0, sizeof(ui_t));

        // UART_putString("Received settings\n");
        // sprintf(buffer, "File descriptor: %d\n", options->fd);
        // UART_putString(buffer);
        // sprintf(buffer, "Channel mask: %d\n", options->channel_msk);
        // UART_putString(buffer);
        // sprintf(buffer, "Frequency: %d\n", options->frequency);
        // UART_putString(buffer);
        // sprintf(buffer, "Mode: %d\n", options->mode);
        // UART_putString(buffer);

        recv = 0;
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

    // else stop
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
                .timestamp = 1,             // TODO: timestamp 
                .value = adc_value,        
                .channel = i};

            send_packet(&packet);
        }
    }
}

void sample_buf(ui_t* options)
{
    UART_putString("Sample buffered not implemented yet\n");
}

void send_packet(packet_t* packet){
  uint8_t* p=(uint8_t*)packet;
  for(uint8_t i=0;i<sizeof(packet_t);++i){
    UART_putChar(*p);
    ++p;
  }
} 