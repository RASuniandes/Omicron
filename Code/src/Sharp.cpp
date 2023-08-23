#include "Sharp.h"

Sharp::Sharp(int pinNumber, int reference) : pin(pinNumber), referenceDegree(reference) {
    pinMode(pin, INPUT);
}

int Sharp::readValue() {
    int digitalValue = digitalRead(pin);
    return digitalValue;
}

int Sharp::calculateDegree() {
    int digitalValue = readValue();
    // Calcula el grado de inclinación en relación con la referencia.
    
    int degree = 180;  // Ajusta el valor de referencia
    
    if (digitalValue == HIGH) {
        degree = referenceDegree;  // Obstáculo a la izquierda (referencia)
    } else {
        degree = 180;   // No hay obstáculo a la izquierda
    }

    return degree;
}