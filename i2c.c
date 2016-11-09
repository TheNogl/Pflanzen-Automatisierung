#include <stdio.h>
#include <wiringPiI2C.h>

int main(void)
{
    unsigned char data=0;
    int f=wiringPiI2CSetup(0x34);
    if(f == -1) printf("Error");
    wiringPiI2CWrite(f, 0x01);
    while(data==0)
    {
	data=(unsigned char)wiringPiI2CRead(f);
    }
    printf("%d", data);
    return 0;
}
