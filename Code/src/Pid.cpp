#include "Pid.h"
#include "Motor.h"

Pid::Pid(float cKp, float cKi, float cKd, int cSetPoint, int Vreference, int numSensors) : Kp(cKp), Ki(cKi), Kd(cKd), setPoint(cSetPoint), _numSensors(numSensors), reference(Vreference), proportional (0), integral(0), derivative(0), proportional_past
(0), control_output(0), position(0), last_value(0) {

}

/**
 * Calcula el error del controlador PID basado en los valores de los sensores.
 *
 * @param sensorsValues Un arreglo de enteros que representa los valores de los sensores.
 * @return El valor del error calculado.
 */
int Pid::calculateError(int* sensorsValues) {

    long avg = 0;
    long sum = 0;
    int on_line = 0;

    for (int i = 0;i < _numSensors;i++) {
        int value = sensorsValues[i];
        if (value > 0) {
            on_line = 1;
        }
        avg += (long)(value) * (i * 10);
        sum += value;
    }
    if (!on_line) {
        if (last_value < 1) {
            return 0;
        }
        else {
            return (_numSensors - 1) * 10;
        }
    }
    last_value = avg / sum;
    return last_value;
}

/**
 * Calcula la salida de control del controlador PID para seguir una posición objetivo.
 *
 * @param sensors La posición actual del sistema.
 * @return La salida de control calculada por el controlador PID.
 */
float Pid::traking(int sensors) {

    position = sensors;

    proportional  = setPoint - (position);
    integral = integral + proportional_past;
    derivative = (proportional  - proportional_past);

    float ITerm = integral * Ki;
    ITerm = constrain(ITerm, -250, 250);

    control_output = (proportional  * Kp) + (derivative * Kd) + ITerm;

    // Saturador del la salida del controlador
    control_output = constrain(control_output, -reference, reference);

    proportional_past = proportional;

    return control_output;
}