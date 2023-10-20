#include <Arduino.h>
#include "Motor.h"

#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

#define UP "u"
#define LEFT "l"
#define DOWN "d"
#define RIGHT "r"

int direccion;
int velocidad;
int angulo;
int jaja;
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

void executecommand(int direccion,int velocidad,int angulo,int jaja){
    int command = direccion;
    Serial.println("Datos");
    Serial.println(direccion);
    Serial.println(velocidad);
    Serial.println(angulo);
    Serial.println(jaja);
  if (direccion == 271 && angulo > 0){  //pa adelante

    motores(velocidad,velocidad);
    //Serial.print("adelante");
    }
  else if (direccion == 271 && 0 > angulo){  //pa adelante

    motores(velocidad,velocidad);
    //Serial.print("adelante");
    }
  else if (direccion == 271){  //pa adelante

    motores(velocidad,velocidad);
    //Serial.print("adelante");
    }
  else if (direccion == 273 && angulo > 0){  //pa atras
    motores(velocidad,velocidad);
    //Serial.print("atras");
    }
  else if (direccion == 273 && 0 > angulo){  //pa atras
    motores(velocidad,velocidad);
    //Serial.print("atras");
    }
  else if (direccion == 273){  //pa atras
    motores(velocidad,velocidad);
    
}


void loop() {
  if (SerialBT.available()) {
    direccion = SerialBT.read();
    velocidad = SerialBT.read();
    angulo = SerialBT.read();
    angulo-=88;
    Serial.print("\n");
    
    executecommand(direccion, velocidad, angulo, jaja);}
  }
