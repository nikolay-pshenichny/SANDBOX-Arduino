#include "Arduino.h"
#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(int pin)
{
	_pin = pin;
}

long Ultrasonic::GetDistance(void)
{
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(_pin, HIGH);
    delayMicroseconds(5);
    digitalWrite(_pin, LOW);
    pinMode(_pin, INPUT);

    long duration = pulseIn(_pin, HIGH);
    return duration/29/2;
}
