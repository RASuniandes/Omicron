#ifndef QTR_H
#define QTR_H

#include <Arduino.h>

class Qtr {
private:
    int pin;

public:
    Qtr(int pinNumber);
    int value();
};

#endif