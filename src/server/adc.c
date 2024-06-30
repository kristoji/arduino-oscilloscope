#include "adc.h"

void adc_init() 
{
    ADMUX = (1<<REFS0);                                         // Reference voltage on AVCC (5V)
    ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);  // Enable ADC, prescaler = 128
}

uint16_t adc_read(uint8_t chnl) 
{
    // Ensure the channel is within the valid range (0-15)
    if (chnl > 15) return 0;

    // Clear MUX5 in ADCSRB
    ADCSRB &= ~(1<<MUX5);
    
    // If the channel is 8 or higher, set MUX5 in ADCSRB
    if (chnl >= 8) {
        ADCSRB |= (1<<MUX5);
        chnl -= 8;
    }

    // Select the lower 4 bits of the channel in ADMUX
    ADMUX = (ADMUX & 0xF0) | (chnl & 0x0F);

    // Start the conversion
    ADCSRA |= (1<<ADSC);

    // Wait for the conversion to complete
    while (ADCSRA & (1<<ADSC));

    // Return the ADC result
    return ADC;
}

