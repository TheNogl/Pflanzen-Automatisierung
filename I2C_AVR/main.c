/*#################################################################################################
	Title	: TWI SLave
	Author	: Martin Junghans <jtronics@gmx.de>
	Hompage	: www.jtronics.de
	Software: AVR-GCC / Programmers Notpad 2
	License	: GNU General Public License

	Aufgabe	:
	Betrieb eines AVRs mit Hardware-TWI-Schnittstelle als Slave.
	Zu Beginn muss init_twi_slave mit der gewünschten Slave-Adresse als Parameter aufgerufen werden.
	Der Datenaustausch mit dem Master erfolgt über die Buffer rxbuffer und txbuffer, auf die von Master und Slave zugegriffen werden kann.
	rxbuffer und txbuffer sind globale Variablen (Array aus uint8_t).

	Ablauf:
	Die Ansteuerung des rxbuffers, in den der Master schreiben kann, erfolgt ähnlich wie bei einem normalen I2C-EEPROM.
	Man sendet zunächst die Bufferposition, an die man schreiben will, und dann die Daten. Die Bufferposition wird
	automatisch hochgezählt, sodass man mehrere Datenbytes hintereinander schreiben kann, ohne jedesmal
	die Bufferadresse zu schreiben.
	Um den txbuffer vom Master aus zu lesen, überträgt man zunächst in einem Schreibzugriff die gewünschte Bufferposition und
	liest dann nach einem repeated start die Daten aus. Die Bufferposition wird automatisch hochgezählt, sodass man mehrere
	Datenbytes hintereinander lesen kann, ohne jedesmal die Bufferposition zu schreiben.

	Abgefangene Fehlbedienung durch den Master:
	- Lesen über die Grenze des txbuffers hinaus
	- Schreiben über die Grenzen des rxbuffers hinaus
	- Angabe einer ungültigen Schreib/Lese-Adresse
	- Lesezuggriff, ohne vorher Leseadresse geschrieben zu haben

	LICENSE:
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

//#################################################################################################*/

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "twislave.h"
#include "twislave.c"
#include "i2c_tasks.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

//###################### Slave-Adresse
#define SLAVE_ADRESSE 0x69 								// Slave-Adresse

//###################### Macros
#define uniq(LOW,HEIGHT)	((HEIGHT << 8)|LOW)			// 2x 8Bit 	--> 16Bit
#define LOW_BYTE(x)        	(x & 0xff)					// 16Bit 	--> 8Bit
#define HIGH_BYTE(x)       	((x >> 8) & 0xff)			// 16Bit 	--> 8Bit
#define NOMINAL_F_AIR 100000


#define sbi(ADDRESS,BIT) 	((ADDRESS) |= (1<<(BIT)))	// set Bit
#define cbi(ADDRESS,BIT) 	((ADDRESS) &= ~(1<<(BIT)))	// clear Bit
#define	toggle(ADDRESS,BIT)	((ADDRESS) ^= (1<<BIT))		// Bit umschalten

#define	bis(ADDRESS,BIT)	(ADDRESS & (1<<BIT))		// bit is set?
#define	bic(ADDRESS,BIT)	(!(ADDRESS & (1<<BIT)))		// bit is clear?

unsigned char adc_volt_measure(unsigned char kanal);

void Initialisierung(void)
{
    cli();
    init_twi_slave(SLAVE_ADRESSE);
    sei();
}

int main(void)
{
    //unsigned char lumred=50, lumblue=50;
    unsigned int frequency=0;
    Initialisierung();
    txbuffer[MOISTURE]=88;
    while(1)
    {
        //if((adc_volt_measure(4)<(txbuffer[MOISTURE]-5))||(adc_volt_measure(4)>(txbuffer[MOISTURE]+5))) txbuffer[MOISTURE]=adc_volt_measure(4);
        //else if((frequency<(txbuffer[AIRMOISTURE]-5))||(frequency>(txbuffer[AIRMOISTURE]+5))) txbuffer[AIRMOISTURE]=(unsigned char)(frequency/NOMINAL_F_AIR);

    }
    return 0;
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
