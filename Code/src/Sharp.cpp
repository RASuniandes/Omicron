#include "Sharp.h"

Sharp::Sharp(int pinNumber, int reference) : pin(pinNumber), referenceDegree(reference) {
    pinMode(pin, INPUT);
}

int Sharp::readValue() {
    int digitalValue = digitalRead(pin);
    return digitalValue;
}

/**
 * Calcula el peso de inclinación en relación con la referencia y le asigna un peso dependiendo de la posición.
 *
 * @return El peso calculado.
 */
float Sharp::calculateWeigth() {
    int sensorValue = readValue();
    // Calcula el peso de inclinación en relación con la referencia y la asigna un peso dependiendo de la posicion.
    float peso = sensorValue * referenceDegree * 10;
    return peso;
}

int Sharp::getWeigth() {
    return referenceDegree;
}