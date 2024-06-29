#include "server.h"

volatile uint8_t channel = 0;

void adc_init() {
    ADMUX = (1<<REFS0);                                         // Reference voltage on AVCC (5V)
    ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);  // Enable ADC, prescaler = 128
}

uint16_t adc_read(uint8_t chnl) {
    ADMUX = (ADMUX & 0xF0) | (chnl & 0x0F);     // Select ADC channel (0 to 15)
    ADCSRA |= (1<<ADSC);                        // Start ADC conversion
    while (ADCSRA & (1<<ADSC));                 // Wait for conversion to complete
    return ADC;                                 // Return ADC result
}

ISR(USART0_RX_vect) 
{
    if (UDR0 <= '9' && UDR0 >= '0')
        channel = (UDR0 - '0') & 0x0F;
}

int main(void) {
    UART_init();
    adc_init();
    
    uint16_t adc_value;
    char buffer[20];

    sei();
    
    while (1) {
        adc_value = adc_read(channel);
        
        sprintf(buffer, "ADC[%d]: %d\r\n", channel, adc_value);
        UART_putString(buffer);
        
        _delay_ms(1000);
    }
    
    return 0;
}