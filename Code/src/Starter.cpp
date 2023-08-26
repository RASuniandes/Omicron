#include "Starter.h"

Starter::Starter(int pinNumber) : pin(pinNumber) {
    pinMode(pin, INPUT);
}

int Starter::getStart() {
    int value = digitalRead(pin);
    return value;
}