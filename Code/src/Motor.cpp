#include "Motor.h"

Motor::Motor(int pinA, int pinB) : inPinA(pinA), inPinB(pinB) {
    pinMode(inPinA, OUTPUT);
    pinMode(inPinB, OUTPUT);
}

void Motor::setSpeed(int speed) {
    // Asegurarse de que la velocidad esté dentro de los límites
    speed = constrain(speed, -255, 255);

    if (speed > 0) {
        analogWrite(inPinA, speed);
        analogWrite(inPinB, 0);
    } else if (speed < 0) {
        analogWrite(inPinA, 0);
        analogWrite(inPinB, -speed);
    } else {
        analogWrite(inPinA, 0);
        analogWrite(inPinB, 0);
    }
}