#include <Arduino.h>
#include "Qtr.h"


Qtr qtr_left(5);
Qtr qtr_right(6);

const int pin_sharp_front = 25;
const int pin_sharp_left = 35;
const int pin_sharp_rigth = 34;
bool comments = true;

//Qtr - Blanco/negro

//Motores
int motor_pin = 26;
int motor_pin_inv = 27;
int motor2_pin = 33;
int motor2_pin_inv = 32;


void Backward(){
  digitalWrite(motor_pin,HIGH);
  digitalWrite(motor2_pin,HIGH);
  digitalWrite(motor_pin_inv,LOW);
  digitalWrite(motor2_pin_inv,LOW);
}

void Twice_left(){
  digitalWrite(motor_pin,LOW);
  digitalWrite(motor2_pin,HIGH);
  digitalWrite(motor_pin_inv,HIGH);
  digitalWrite(motor2_pin_inv,LOW);
}

void Twice_right(){
  digitalWrite(motor_pin,HIGH);
  digitalWrite(motor_pin_inv,LOW);
  digitalWrite(motor2_pin,LOW);
  digitalWrite(motor2_pin_inv,HIGH);
}  

void Fordward(){
  digitalWrite(motor_pin,LOW);
  digitalWrite(motor2_pin,LOW);
  digitalWrite(motor_pin_inv,HIGH);
  digitalWrite(motor2_pin_inv,HIGH);
}
void STOP(){
  digitalWrite(motor_pin,LOW);
  digitalWrite(motor2_pin,LOW);
  digitalWrite(motor_pin_inv,LOW);
  digitalWrite(motor2_pin_inv,LOW);
}


void setup() {
  // put your setup code here, to run once:

    pinMode(motor_pin,OUTPUT);
    pinMode(motor2_pin,OUTPUT);
    pinMode(motor_pin_inv,OUTPUT);
    pinMode(motor2_pin_inv,OUTPUT);
    pinMode(pin_sharp_front,INPUT);
    pinMode(pin_sharp_left,INPUT);
    pinMode(pin_sharp_rigth,INPUT);
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