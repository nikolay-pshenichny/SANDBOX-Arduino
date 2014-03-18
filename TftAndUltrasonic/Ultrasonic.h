#ifndef _ULTRASONIC_H
#define _ULTRASONIC_H

class Ultrasonic
{
    public:
        Ultrasonic(int pin);
        long GetDistance(void);
        
    private:
        int _pin;
};

#endif
