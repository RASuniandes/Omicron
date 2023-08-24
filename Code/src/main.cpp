#include <Arduino.h>
#include "Qtr.h"
#include "Motor.h"
#include "Sharp.h"

//Qtr - Blanco/negro

Qtr qtr_left(4);
Qtr qtr_right(5);

// Sharps sensors
Sharp s1(18, -50); //Sensor_1
Sharp s2(19, -25); //Sensor_2
Sharp s3(13, 0); //Sensor_3
Sharp s4(25, 25); //Sensor_4
Sharp s5(23, 50); //Sensor_5


//Motores

Motor motor_a(26,27);
Motor motor_b(33,32);

boolean comments=true;


////////////////////Constantes PID////////////////////////
int velocidad=255; //aqui cambias velocidad  0-100        //
float KP=35.78;  //25.78  , 35.78                               //
float KD=110;     //20     ,50                           //
float KI=0;     //       ,0                            //
                          //
////////////////////////////////////////////////////////
 
/////////////Otras Variables auxiliares///////////////////////////////////////
  int _numSensors=5; //cantidad de sensores usados
  int sensors_values[5]; //numero de sensores usados
  int last_value=0;
 
  int btn1=0,btn2=0,btn3=0;
  int s1_value=0,s2_value=0,s3_value=0,s_value4=0;
  int posicion;
  int proporcional=0;
  int integral=0;
  int derivativo=0;
  int proporcional_pasado=0;
  int salida_control=0;
  int caso=0;
//////////////////////////////////////////////////////


void Backward(){
  motor_a.setSpeed(-255);
  motor_b.setSpeed(-255);
}
void Twice_left(){
  motor_a.setSpeed(255);
  motor_b.setSpeed(-255);

}
void Twice_right(){
  motor_a.setSpeed(-255);
  motor_b.setSpeed(255);
}  
void Fordward(){
  motor_a.setSpeed(255);
  motor_b.setSpeed(255);
}
void STOP(){
  motor_a.setSpeed(0);
  motor_b.setSpeed(0);
}


float ponderacion(){

  posicion=s1.calculateDegree()+s2.calculateDegree()+s3.calculateDegree()+s4.calculateDegree()+s5.calculateDegree();
  Serial.println(posicion);
  return posicion;
}

void motores(int speed_m_left, int speed_m_right){
  motor_a.setSpeed(speed_m_left);
  motor_b.setSpeed(speed_m_right);

}


void tracking3() // envestida
{
  posicion=ponderacion();
  proporcional=(posicion) - 10;
  integral=integral+proporcional_pasado;
  derivativo=(proporcional-proporcional_pasado);
  int ITerm=integral*KI;
  if(ITerm>=250)ITerm=250;
  if(ITerm<=-250)ITerm=-250;
 
  salida_control=(proporcional*KP)+(derivativo*KD)+ITerm;
 
  if(salida_control>velocidad) salida_control=velocidad;
  if(salida_control<-velocidad) salida_control=-velocidad;

                     
  if(salida_control<0)//si se salio por la izquierda
  {
 
    motores(velocidad,velocidad+salida_control);
  }
  if(salida_control>0)//si se salio por la derecha
  {
     motores(velocidad-salida_control , velocidad);
  }
   if(salida_control==0)//si se salio por la derecha
  {
     motores(velocidad , velocidad);
  }

  // Serial.println(salida_control);
  proporcional_pasado=proporcional;
 
}



void setup() {
  // put your setup code here, to run once:

    if ( comments == true){
      Serial.begin(9600);
    }
    
}




void loop() {
  delay(2000);
  Fordward();

  //digitalWrite(motor2_pin,HIGH);
  //digitalWrite(motor2_pin_inv,LOW);
  //digitalWrite(motor_pin,HIGH);
  //digitalWrite(motor_pin_inv,LOW);

  Serial.println("adelante");
  delay(2000);
  STOP();
  
  delay(2000);
}