#include <avr/io.h>

void USART_Init(unsigned int baud);
void USART_Transmit(unsigned char data);
unsigned char adc_volt_measure(unsigned char kanal); //kanal 0 bis 13 8bit auflösung

int main(void)
{
    CLKPR = 0x80;
    CLKPR = 0x00;
    USART_Init(9600);
    unsigned char measure = 0;

    while(1)
    {
        USART_Transmit(adc_volt_measure(0));
    }

    return 0;
}

void USART_Init( unsigned int baud )
{
    UBRRHn = (unsigned char)(baud>>8);
    UBRRLn = (unsigned char)baud;
    UCSRnB = (1<<RXENn)|(1<<TXENn);
    //8data, 2stop bit
    UCSRnC = (1<<USBSn)|(3<<UCSZn0);
}

void USART_Transmit( unsigned char data )
{
    /* Wait for empty transmit buffer */
    while ( !( UCSRnA & (1<<UDREn)) )
        ;
    /* Put data into buffer, sends the data */
    UDRn = data;
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

