#include "Sharp.h"

Sharp::Sharp(int pinNumber, int reference) : pin(pinNumber), referenceDegree(reference) {
    pinMode(pin, INPUT);
}

int Sharp::readValue() {
    int digitalValue = digitalRead(pin);


    return digitalValue;
}

float Sharp::calculateDegree() {
    int sensorValue = readValue();
    // Calcula el grado de inclinación en relación con la referencia y la asigna un peso dependiendo de la posicion.
    float angulo_desfase_rad = radians(referenceDegree);
    float cos_angulo_desfase = cos(angulo_desfase_rad);

    float peso=sensorValue*cos_angulo_desfase;

    return peso;
}