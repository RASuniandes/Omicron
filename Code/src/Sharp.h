#ifndef SHARP_H
#define SHARP_H

#include <Arduino.h>

/**
 * @brief Clase que representa un sensor Sharp.
 *
 * Esta clase permite interactuar con un sensor Sharp para medir distancias y calcular pesos.
 */
class Sharp {
    private:
    int pin;
    int referenceDegree;

    public:
    /**
     * @brief Constructor de la clase Sharp.
     *
     * @param pinNumber El número de pin al que está conectado el sensor.
     * @param reference El valor de referencia para el cálculo del peso.
     */
    Sharp(int pinNumber, int reference);

    /**
     * @brief Lee el valor del sensor Sharp.
     *
     * @return El valor leído del sensor.
     */
    int readValue();

    /**
     * @brief Calcula el peso a partir del valor leído del sensor.
     *
     * @return El peso calculado.
     */
    float calculateWeigth();

    /**
     * @brief Obtiene el peso calculado.
     *
     * @return El peso calculado.
     */
    int getWeigth();
};

#endif