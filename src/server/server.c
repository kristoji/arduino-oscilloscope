#include "server.h"

volatile uint8_t channel = 0;

int main(void) {
    UART_init();
    adc_init();
    
    uint16_t adc_value;
    char buffer[1024];

    sei();
    
    while (1) {
        adc_value = adc_read(channel);
        
        sprintf(buffer, "ADC[%d]: %d\r\n", channel, adc_value);
        UART_putString(buffer);

        handle_settings(&options);
        
        _delay_ms(1000);
    }
    
    return 0;
}