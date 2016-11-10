#define MOISTURE 0x01 //Answer: ADC-Measurement
#define TEMP 0x02 //Answer: ADC-Measurement
#define AIRMOISTURE 0x03 //Answer: Oszillator Frequency/Nominal Frequency*128
#define LUMINOSITY_RED 0x04 //Answer: Percent 0-100
#define LUMINOSITY_BLUE 0x05 //Answer: Percent 0-100
#define TIME_WATER_D 0x06 //Answer: Time since last watering days
#define TIME_WATER_H 0x07 //Answer: Time since last watering hours
#define TIME_WATER_M 0x08 //Answer: Time since last watering minutes
#define TIME_START_D 0x09 //Answer: Time since startup days
#define TIME_START_H 0x0A //Answer: Time since startup hours
#define TIME_START_M 0x0B //Answer: Time since startup minutes
#define CHANGE_TEMP_1 0x0C //Answer: 0xAA
#define CHANGE_TEMP_NEG1 0x0D //Answer: 0xAB
#define CHANGE_TEMP_5 0x0E //Answer: 0xAC
#define CHANGE_TEMP_NEG5 0x0F //Answer: 0xAD
#define CHANGE_LUMINOSITY_RED_1 0x10 //Answer: 0xAE
#define CHANGE_LUMINOSITY_RED_NEG1 0x11 //Answer: 0xAF
#define CHANGE_LUMINOSITY_RED_5 0x12 //Answer: 0xB1
#define CHANGE_LUMINOSITY_RED_NEG5 0x13 //Answer: 0xB2
#define CHANGE_LUMINOSITY_BLUE_1 0x14 //Answer: 0xB3
#define CHANGE_LUMINOSITY_BLUE_NEG1 0x15 //Answer: 0xB4
#define CHANGE_LUMINOSITY_BLUE_5 0x16 //Answer: 0xB5
#define CHANGE_LUMINOSITY_BLUE_NEG5 0x17 //Answer: 0xB6
