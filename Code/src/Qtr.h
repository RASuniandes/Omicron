#ifndef QTR_H
#define QTR_H

#include <Arduino.h>

/**
 * @brief Clase que representa un sensor Qtr.
 *
 * Esta clase permite interactuar con un sensor Qtr para obtener su valor.
 */
class Qtr {
    private:
    int pin;

    public:
    /**
     * @brief Constructor de la clase Qtr.
     *
     * @param pinNumber El número de pin al que está conectado el sensor.
     */
    Qtr(int pinNumber);

    /**
     * @brief Obtiene el valor del sensor Qtr.
     *
     * @return El valor del sensor Qtr.
     */
    int value();
};

#endif