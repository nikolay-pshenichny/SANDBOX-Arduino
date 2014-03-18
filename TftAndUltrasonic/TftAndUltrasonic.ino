#include <stdint.h>
#include "Arduino.h"

#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include "Ultrasonic.h"
#include "Display.h"
// -------------------------

#define RangeSensorConnectionPort 53
#define MaxDistanceValue 400
// -------------------------

Ultrasonic * ultrasonic;
Display * displ;
// -------------------------

void setup()
{
    Serial.begin(9600);
     
    ultrasonic = new Ultrasonic(RangeSensorConnectionPort);
    displ = new Display(MaxDistanceValue);
}

void loop()
{
    long distance = ultrasonic->GetDistance();

    displ->Update(distance);

    delay(100);
}
