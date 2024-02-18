#ifndef PID_H
#define PID_H

#include <Arduino.h>

/**
 * @brief Clase que implementa un controlador PID.
 */
class Pid {
    private:

    float Kp;
    float Ki;
    float Kd;
    int _numSensors;
    int setPoint;
    int reference;
    int posicion;
    int proporcional;
    int integral;
    int derivativo;
    int proporcional_pasado;
    float salida_control;
    int last_value;


    public:
    /**
     * @brief Constructor de la clase Pid.
     * @param cKp Valor del coeficiente proporcional.
     * @param cKi Valor del coeficiente integral.
     * @param cKd Valor del coeficiente derivativo.
     * @param cSetPoint Valor del punto de consigna.
     * @param Vreference Valor de referencia.
     * @param numSensors Número de sensores.
     */
    Pid(float cKp, float cKi, float cKd, int cSetPoint, int Vreference, int numSensors);

    /**
     * @brief Método para realizar el seguimiento de la posición.
     * @param position Posición actual.
     * @return Valor de salida del controlador.
     */
    float traking(int position);

    /**
     * @brief Método para calcular el error.
     * @param sensors_values Valores de los sensores.
     * @return Valor del error calculado.
     */
    int calculateError(int* sensors_values);

};

#endif