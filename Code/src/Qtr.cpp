#include "Qtr.h"

Qtr::Qtr(int pinNumber) : pin(pinNumber) {
    pinMode(pin, INPUT);
}

int Qtr::value() {
    int analogReading = analogRead(pin);
    int digitalValue = (analogReading > 512) ? 1 : 0;
    return digitalValue;
}