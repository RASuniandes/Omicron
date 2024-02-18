#include "Starter.h"

/**
 * @brief Constructor de la clase Starter.
 *
 * @param pinStartNumber Número del pin de inicio.
 * @param pinStopNumber Número del pin de parada.
 */
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