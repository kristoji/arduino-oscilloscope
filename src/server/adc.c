#include "adc.h"

void adc_init() 
{
    ADMUX = (1<<REFS0);                                         // Reference voltage on AVCC (5V)
    ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);  // Enable ADC, prescaler = 128
}

uint16_t adc_read(uint8_t chnl) 
{
    ADMUX = (ADMUX & 0xF0) | (chnl & 0x0F);     // Select ADC channel (0 to 15)
    ADCSRA |= (1<<ADSC);                        // Start ADC conversion
    while (ADCSRA & (1<<ADSC));                 // Wait for conversion to complete
    return ADC;                                 // Return ADC result
}
