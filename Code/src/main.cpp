#include <Arduino.h>
#include "Qtr.h"
#include "Motor.h"
#include "Sharp.h"
#include "Starter.h"
#include "Pid.h"

//Qtr - Blanco/negro
Qtr qtr_left(4);
Qtr qtr_right(25);

// Sharps sensors
Sharp s1(18, 0); //Sensor_1
Sharp s2(19, 1); //Sensor_2
Sharp s3(13, 2); //Sensor_3
Sharp s4(23, 3); //Sensor_4
Sharp s5(5, 4); //Sensor_5

//Motores
Motor motor_a(27,226);
Motor motor_b(32,33);

//Starter 
Starter start(21,14);

//Comentarios
boolean comments=true;

//Otras Variables auxiliares
int _numSensors=5; //cantidad de sensores usados
int sensorValues[5];
 
//PID




float L=0.01;
float T=0.1;
float K=2.5;

int reference = 80;
float Kp = 1.2*(T/(K*L)); //1.2 *(T)/KL
float Ki = 2*L; //2L
float Kd =0.5*L;//0.5L
Pid pid(Kp, Ki, Kd, 20, 60, _numSensors);


int* getSharpValues() {

  sensorValues[0] = s1.readValue();
  sensorValues[1] = s2.readValue();
  sensorValues[2] = s3.readValue();
  sensorValues[3] = s4.readValue();
  sensorValues[4] = s5.readValue();  
  return sensorValues;
}

void motores(int speed_m_left, int speed_m_right){
  Serial.print("motorA SPEED");
  Serial.println(speed_m_left);

  Serial.print("motorB SPEED");
  Serial.println(speed_m_right);

  motor_a.setSpeed(speed_m_left);
  motor_b.setSpeed(speed_m_right);
  //delay(300);
}


void show_sensors(){
  Serial.print("qtr_lef: ");
  Serial.print(qtr_left.value());
  Serial.print("  qtr_right: ");
  Serial.print(qtr_right.value());
  Serial.print(" s1: ");
  Serial.print(s1.readValue());
  Serial.print(" s2: ");
  Serial.print(s2.readValue());
  Serial.print(" s3: ");
  Serial.print(s3.readValue());
  Serial.print(" s4: ");
  Serial.print(s4.readValue());
  Serial.print(" s5: ");
  Serial.println(s5.readValue());
  Serial.print("Starter: ");
  Serial.println(start.getStart());
  Serial.print("Stop: ");
  Serial.println(start.getStop());
  //delay(1000);


}




void setup() {
  // put your setup code here, to run once:

    if ( comments == true){
      Serial.begin(9600);
    }
    delay(2000); 
}


void loop() {
  
  int* values = getSharpValues();

  //Serial.print("Sensores: ");
  //show_sensors();

  float salida_control = pid.traking(values);
 

  Serial.print("Salida de control:");
  Serial.println(salida_control);
  // delay(500);
  // if (start.getStart()==HIGH && start.getStop()==LOW){
    // motores(-255,-255);
  // }
  // else{

  //   motores(0,0);
  // }

  if(salida_control<0) { 
    motores(reference-salida_control, reference);
  }

  if(salida_control>0) { 
    motores(reference, reference+salida_control);
  }

  if(salida_control==0) {  
    motores(reference , reference);
  }
  Serial.println("");
  //delay(300);

}