#include "server.h"

volatile uint8_t channel = 0;

int main(void) {
    UART_init();
    adc_init();

    options.mode = 2;           // stop as default
    
    sei();
    
    while (1) {
        handle_settings(&options);

        sample(&options);
        
        _delay_ms(1000);        // find a way to use the frequency
    }
    
    return 0;
}