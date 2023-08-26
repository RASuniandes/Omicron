#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
private:
    int inPinA;
    int inPinB;

public:
    Motor(int pinA, int pinB);
    void setSpeed(int speed);
};

#endif