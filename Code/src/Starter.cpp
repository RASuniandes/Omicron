#include "Starter.h"

Starter::Starter(int pinStartNumber, int pinStopNumber) : pinStart(pinStartNumber), pinStop(pinStopNumber) {
    pinMode(pinStart, INPUT);
    pinMode(pinStop, INPUT);
}

int Starter::getStart() {
    int startValue = digitalRead(pinStart);
    return startValue;
}

int Starter::getStop() {
    int stopValue = digitalRead(pinStop);
    return stopValue;
}