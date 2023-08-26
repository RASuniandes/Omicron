#ifndef STARTER_H
#define STARTER_H

#include <Arduino.h>

class Starter {
private:
    int pin;

public:
    Starter(int pinNumber);
    int getStart();
};

#endif