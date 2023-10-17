#include "Qtr.h"

Qtr::Qtr(int pinNumber) : pin(pinNumber) {
    pinMode(pin, INPUT);
}

int Qtr::value() {
    int analogReading = analogRead(pin);
    //Serial.println(analogReading);
    int digitalValue = (analogReading > 900) ? 1 : 0;
    //Serial.println(digitalValue);
    return digitalValue;
}