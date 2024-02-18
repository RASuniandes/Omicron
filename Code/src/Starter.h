#ifndef STARTER_H
#define STARTER_H

#include <Arduino.h>

/**
 * @brief Clase que representa un objeto Starter.
 *
 * Esta clase se utiliza para controlar el inicio y detención de un proceso.
 * Tiene dos pines asociados, uno para iniciar y otro para detener el proceso.
 */
class Starter {
    private:
    int pinStart;
    int pinStop;

    public:
    /**
     * @brief Constructor de la clase Starter.
     *
     * @param pinStartNumber Número del pin asociado al inicio del proceso.
     * @param pinStopNumber Número del pin asociado a la detención del proceso.
     */
    Starter(int pinStartNumber, int pinStopNumber);

    /**
     * @brief Obtiene el número del pin asociado al inicio del proceso.
     *
     * @return Número del pin de inicio.
     */
    int getStart();

    /**
     * @brief Obtiene el número del pin asociado a la detención del proceso.
     *
     * @return Número del pin de detención.
     */
    int getStop();
};

#endif