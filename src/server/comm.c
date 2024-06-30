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
        UART_putString("Received settings\n");
        sprintf(buffer, "File descriptor: %d\n", options->fd);
        UART_putString(buffer);
        sprintf(buffer, "Channel mask: %d\n", options->channel_msk);
        UART_putString(buffer);
        sprintf(buffer, "Frequency: %d\n", options->frequency);
        UART_putString(buffer);
        sprintf(buffer, "Mode: %d\n", options->mode);
        UART_putString(buffer);

        recv = 0;
    }
}
