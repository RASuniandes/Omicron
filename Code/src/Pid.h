#ifndef PID_H
#define PID_H

#include <Arduino.h>

class Pid {
private:
    
    int Kp;
    int Ki;
    int Kd;
    int _numSensors;
    int setPoint;
    int reference;
    int posicion;
    int proporcional;
    int integral;
    int derivativo;
    int proporcional_pasado;
    int salida_control;
    int last_value;
    

public:
    Pid(int cKp, int cKi, int cKd, int cSetPoint, int Vreference, int numSensors);
    float traking(int* sensors_values);
    int calculateError(int* sensors_values);

};

#endif