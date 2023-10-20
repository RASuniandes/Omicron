#include "Pid.h"
#include "Motor.h"

Pid::Pid(float cKp, float cKi, float cKd, int cSetPoint, int Vreference, int numSensors) : Kp(cKp), Ki(cKi), Kd(cKd), setPoint(cSetPoint), _numSensors(numSensors), reference(Vreference), proporcional(0), integral(0), derivativo(0), proporcional_pasado(0), salida_control(0), posicion(0), last_value(0) {
    

}

int Pid::calculateError(int* sensorsValues) {
    
    long avg=0;
    long sum=0;
    int on_line=0;

    for (int i=0;i<_numSensors;i++) {

        int value=sensorsValues[i];
        
        if (value>0) {

            on_line=1;
        
        }

        avg+=(long)(value)*(i*10);
        sum+=value;
    }

    if (!on_line) {

        if (last_value<1) {

            return 0;
        
        } else {

            return (_numSensors-1)*10;
            
        }
    }

    last_value = avg/sum;
    return last_value;
}

float Pid::traking(int position) {
    
    posicion = position;

    proporcional=(posicion) - setPoint;
    integral = integral + proporcional_pasado;
    derivativo = (proporcional-proporcional_pasado);

    float ITerm=integral*Ki;
    if(ITerm>=250)ITerm=250;
    if(ITerm<=-250)ITerm=-250;
    
    salida_control=(proporcional*Kp)+(derivativo*Kd)+ITerm;
    
    if(salida_control>reference) salida_control=reference;
    if(salida_control<-reference) salida_control=-reference;

    proporcional_pasado=proporcional;

    return salida_control;
}