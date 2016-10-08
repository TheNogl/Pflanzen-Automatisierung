//100kbit/s
//F_CPU = 16MHz
//Slave Address ist 0x69

#include <avr/io.h>

#define SLAVE_READ 0x60
#define SLAVE_WRITE 0xA8

#define MOISTURE 0x01
#define TEMP 0x02

char init_spi(unsigned char addr, unsigned int bitrate); //Bitrate in Kbit/s
void slave_send(unsigned char data); //1 Byte wird gesendet
unsigned char slave_read_ack (void); //1 Byte wird eingelesen und erhalt bestätigt
unsigned char slave_action(unsigned char *actiontype); //auszuführende aktion wird abgerufen

unsigned char adc_volt_measure(unsigned char kanal); //kanal 0 bis 13 8bit auflösung

int main(void)
{
    CLKPR = 0x80;
    CLKPR = 0x00;
    unsigned char datain=0;
    unsigned char dataout=0;
    unsigned char actiontype;
    if(!init_spi(69, 100)) return 0;

    while(1)
    {
        if (slave_action(&actiontype))
        {
            switch(actiontype)
            {
            case SLAVE_READ:
                datain = slave_read_ack();
                break;

            case SLAVE_WRITE:
                slave_send(dataout);
                datain = 0;
                break;
            }
        }
        switch(datain)
        {
        case MOISTURE:
            dataout = adc_volt_measure(0);
            break;

        case TEMP:
            dataout = adc_volt_measure(1);
            break;
        }
    }

    return 0;
}

char init_spi(unsigned char addr, unsigned int bitrate)
{
    TWBR = ((F_CPU/bitrate)-16)/2;
    if (TWBR < 11) return 0;
    TWAR = (addr << 1);
    TWCR = 0x44;
    return 1;
}

void slave_send(unsigned char data)
{
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA); //signal zum senden
    while (!(TWCR & (1<<TWINT))); //warten bis vollständig empfangen
}

unsigned char slave_read_ack (void)
{
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA); //daten einlesen
    while (!(TWCR & (1<<TWINT))); //warten bis daten vollständig und ack gesendet
    return TWDR;
}

unsigned char slave_action(unsigned char *actiontype)
{
    *actiontype = TWSR;
    return TWCR & (1<<TWINT);
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
