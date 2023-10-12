#include <Arduino.h>
#include "Qtr.h"
#include "Motor.h"
#include "Sharp.h"
#include "Starter.h"
#include "Pid.h"

//Qtr - Blanco/negro
Qtr qtr_left(4);
Qtr qtr_right(25);

int qtr_left_value;
int qtr_right_value;

// Sharps sensors
Sharp s1(18, 0); //Sensor_1
Sharp s2(19, 1); //Sensor_2
Sharp s3(13, 2); //Sensor_3
Sharp s4(23, 3); //Sensor_4
Sharp s5(5, 4); //Sensor_5

//Motores
Motor motor_b(27,26);
Motor motor_a(33,32);



//Starter 
Starter start(21,14);

//Comentarios
bool comments= true;

//Otras Variables auxiliares
int _numSensors=5; //cantidad de sensores usados
int sensorValues[5];
 
//PID
unsigned long time_motores = 0;
bool get_in = false;

int time_backward=600; // Constante de tiempo reversa  total
int time_backward_twist=400; // constante de tiempo del giro por lo tato menor a time_backward
int velocity_backward=150;



// float L=0.01;
// float T=0.1;
// float K=2.5;  

int reference = 250;
int z=40;
// float Kp = 1.2*(T/(K*L)); //1.2 *(T)/KL
// float Ki = 2*L; //2L
// float Kd =0.5*L;//0.5L
// float Kp = 22.5;
// float Ki = 0;
//float Kd = 2.5;
float Kp = 3;
float Ki = 0;
float Kd = 0.2;

Pid pid(Kp, Ki, Kd, 20, reference, _numSensors);


int* getSharpValues() {

  sensorValues[0] = s1.readValue();
  sensorValues[1] = s2.readValue();
  sensorValues[2] = s3.readValue();
  sensorValues[3] = s4.readValue();
  sensorValues[4] = s5.readValue();  
  return sensorValues;
}

void motores(int speed_m_left, int speed_m_right){
  Serial.print("motorA SPEED: ");
  Serial.println(speed_m_left);

  Serial.print("motorB SPEED: ");
  Serial.println(speed_m_right);

  motor_a.setSpeed(speed_m_left);
  motor_b.setSpeed(speed_m_right);
  
}


void show_sensors(){
  Serial.print("qtr_lef: ");
  Serial.print(qtr_left_value);
  Serial.print("  qtr_right: ");
  Serial.print(qtr_right_value);
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

}


void Twist_reverse(int direction){

  // si direction es igual 0 es qtr_left
  int motorA_velocity =0;
  int motorB_velocity =0;
  if (direction==1){

    motorA_velocity=-velocity_backward-40;
    motorB_velocity=-velocity_backward;

  }
  else{
    
    motorA_velocity=-velocity_backward;
    motorB_velocity=-velocity_backward-40;

  }

  unsigned long startTime = millis();
  while (millis() - startTime < time_backward ){


      if (millis() - startTime < (time_backward-time_backward_twist)) {
        Serial.println("atras");
        
        motores(-250,-250);
      // Código para el primer intervalo de reversa
      } else {
        // Código para el intervalo restante de giro en segundos
        Serial.println("giro");
        motores(motorA_velocity,motorB_velocity);

      }  
    }
}


void getIn(int qtr_left_value, int qtr_right_value){

  if (qtr_right_value == 0 && qtr_left_value ==1) {
    //Serial.println("qtr_right");
    Twist_reverse(1); 
  }
        
  else if (qtr_right_value == 1 && qtr_left_value ==0) {
    //Serial.println("qtr_left");
    Twist_reverse(0);
  }

  else if (qtr_right_value == 0 && qtr_left_value == 0){

    //Serial.println("qtr_left && qtr_right");
    Twist_reverse(1);
      
  } else {
    //Serial.println("Caso xd que nunca pasa pero pos mejo");
    Twist_reverse(1);
  }
}


void tracking(){
  int* values = getSharpValues();
  int salida_control = pid.traking(values);    
  

  if(salida_control<0) { 

    motores( salida_control - z, reference );

  } else if(salida_control>0) { 
    motores(reference, -salida_control - z);

  } else {  
    motores(250 , 250);
    
  }
}

void gameStart(){

  qtr_left_value = qtr_left.value();
  qtr_right_value = qtr_right.value();

  if (qtr_left_value==1 && qtr_right_value==1){
    
    tracking();
    //motores(50,50);
    

  } else{
    //Serial.println("Get in");
    getIn(qtr_left_value, qtr_right_value);
 
  } 
}

void setup() {
  // put your setup code here, to run once:

    if ( comments == true){
      Serial.begin(9600);
    } 
 
}


void loop() {
  if (start.getStart()==1){
  
    gameStart();
    //tracking();
    //motores(255, 255);
    

  } else {
    motores(0,0);
  }

  //show_sensors();


}