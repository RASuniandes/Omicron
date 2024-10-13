#include "Qtr.h"

Qtr::Qtr(int pinNumber) : pin(pinNumber) {
    pinMode(pin, INPUT);
}

/**
 * Obtiene el valor digital del sensor Qtr.
 *
 * @return El valor digital del sensor Qtr (0 o 1).
 */
int Qtr::value() {
    int analogReading = analogRead(pin);
    int digitalValue = (analogReading > 1700) ? 1 : 0;
    return digitalValue;
}