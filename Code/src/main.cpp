#include <Arduino.h>
#include "Motor.h"

#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

#define UP "u"
#define LEFT "l"
#define DOWN "d"
#define RIGHT "r"

int command;
int Start;
int xd= 83;


//Motores
Motor motor_b(27,26);
Motor motor_a(33,32);
 

void motores(int speed_m_left, int speed_m_right){

  motor_a.setSpeed(speed_m_left);
  motor_b.setSpeed(speed_m_right);
  
}


void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    SerialBT.begin("ESP32_test_prod"); //Bluetooth device name
    Serial.println("The device started, now you can pair it with bluetooth!");
     
}

void executecommand(int command){
    Serial.print(command);
    Serial.print(xd);
  if (command == 70){  //pa adelante
    motores(xd,xd);
    //Serial.print("adelante");
    }
  else if (command == 76){ //pa izquierda 
    motores(-xd,xd);
    }
  else if (command == 71){ //pa diag izquierda
    motores(-xd/2,xd);
    } 
  else if (command == 82){ //pa derecha
    motores(xd,-xd);
    }
  else if (command == 73){ //pa diagderecha
    motores(xd,-xd/2);
    }
  else if (command == 66){ //pa atras
    motores(-xd,-xd);
    }
  else if(command == 83){
    motores(0,0);}
  else if(command == 49){
    xd=0;}
  else if(command == 53){
    xd=83;}
  else if(command == 56){
    xd=180;}
  else if(command == 1133535){
    xd=255;}
}


void loop() {
  if (SerialBT.available()) {
    command = SerialBT.read();
    Serial.print("\n");
    
    executecommand(command);}
  }
