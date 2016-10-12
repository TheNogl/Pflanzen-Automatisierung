#include <avr/io.h>

#define F_CPU 16000000UL
#define BAUD 9600UL
#define UBRR_CALC (F_CPU/16UL/BAUD-1)

void USART_Transmit(unsigned char data);
unsigned char adc_volt_measure(unsigned char kanal); //kanal 0 bis 13 8bit auflösung
void init_usart (void);

int main(void)
{
    CLKPR = 0x80;
    CLKPR = 0x00;
    init_usart();

    while(1)
    {
        USART_Transmit(adc_volt_measure(0));
    }

    return 0;
}

void init_usart (void)
{
UBRR1H = (unsigned char)(UBRR_CALC>>8);
UBRR1L = (unsigned char)(UBRR_CALC);
UCSR1B |= (1<<RXEN1)|(1<<RXCIE1)|(1<<TXEN1);
UCSR1C |= (1<<UCSZ11)|(1<<UCSZ10);
}

void USART_Transmit( unsigned char data )
{
    /* Wait for empty transmit buffer */
    while ( !( UCSR1A & (1<<UDRE1)) )
        ;
    /* Put data into buffer, sends the data */
    UDR1 = data;
}

unsigned char adc_volt_measure(unsigned char kanal)
{
    unsigned char result=0;
    ADMUX=0;
    ADMUX |= (1<<ADLAR) | kanal;
    ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS0);
    ADCSRA |= (1<<ADSC);
    while(ADCSRA & (1<<ADSC));
    result=ADCH;
    return result;
}


