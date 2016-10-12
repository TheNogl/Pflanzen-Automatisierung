#ifndef IOPIN_H
#define IOPIN_H

#include <sys/mman.h>
#include <fcntl.h>

typedef bool t_1bit;

class GPIO
{
public:
    GPIO(int n);

    virtual bool configure() = 0;

    enum PUD{pullUP, pullDown};
    enum FUNC{IN, OUT, ALT};

protected:
    void setFunction(FUNC f);
    void set();
    void clear();
    void setPUD(PUD p);

    int portN;

    int memAcc;
    u_int32_t *mem;
};

class DigitalIn : public GPIO
{
public:
    DigitalIn(int n);
    bool configure() override;

    int read();
    friend DigitalIn& operator>>(DigitalIn& pin, t_1bit& val);
};

class DigitalOut : public GPIO
{
public:
    DigitalOut(int n);
    bool configure() override;

    void write(t_1bit val);
    DigitalOut& operator<<(t_1bit val);
};



#endif // IOPIN_H
