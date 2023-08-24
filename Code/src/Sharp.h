#ifndef SHARP_H
#define SHARP_H

#include <Arduino.h>

class Sharp {
private:
    int pin;
    int referenceDegree;

public:
    Sharp(int pinNumber, int reference);
    int readValue();
    float calculateDegree();
};

#endif