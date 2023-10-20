#ifndef PID_H
#define PID_H

#include <Arduino.h>

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
    Pid(float cKp, float cKi, float cKd, int cSetPoint, int Vreference, int numSensors);
    float traking(int position);
    int calculateError(int* sensors_values);

};

#endif