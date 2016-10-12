#include "iopin.h"

#include <stdlib.h>

GPIO::GPIO(int n) : portN(n)
{

}

void GPIO::setFunction(FUNC f)
{
    //memAcc = open("/dev/mem", O_RDWR | O_SYNC);
    //mem = (u_int32_t*) mmap(NULL, 4*0x64, (PROT_READ | PROT_WRITE), MAP_SHARED, memAcc, 0x3F000000);
    switch(f)
    {
        case FUNC::IN:
            break;

        case FUNC::OUT:
            break;

        case FUNC::ALT:
            break;
    }
}

void GPIO::setPUD(PUD p)
{
    switch(p)
    {
        case PUD::pullDown:
            break;

        case PUD::pullUP:
            break;
    }
}

DigitalIn::DigitalIn(int n) : GPIO(n)
{

}

bool DigitalIn::configure()
{
    setFunction(FUNC::IN);
    setPUD(PUD::pullDown);
    return true;
}

DigitalOut::DigitalOut(int n) : GPIO(n)
{

}

bool DigitalOut::configure()
{
    setFunction(FUNC::OUT);
    return true;
}
