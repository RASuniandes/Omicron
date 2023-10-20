#include <Arduino.h>
#include "Motor.h"
#include "math.h"
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

// variables de recepcion
int direccion;
int velocidad;
int angulo;
int jaja;// este valor no significa nada por eso su nombre

// constantes de proporcion
float L = 0.99; //motor izquierdo
float R = 1;    //motor derecho

//variables temporales
float seno;
float coseno;

//variables de los motores
int vel_left;
int vel_right;

// Motores
Motor motor_b(27, 26);
Motor motor_a(33, 32);

void motores(int speed_m_left, int speed_m_right) {

  motor_a.setSpeed(speed_m_left);
  motor_b.setSpeed(speed_m_right);
}

void setup() {

  Serial.begin(9600);
  SerialBT.begin("ESP32_test_prod"); // incializacion de la conexion bluetooth
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void executecommand(int direccion, int velocidad, int angulo) {
  angulo = PI*180/angulo;
  seno = sinf(angulo);
  coseno = cosf(angulo);
  vel_right = direccion*velocidad*int(R*coseno + L*-seno);
  vel_left = direccion*velocidad*int(R*seno + L*coseno);
  motores(vel_left, vel_right);
}

void loop()
{
  if (SerialBT.available())
  {
    direccion = SerialBT.read();
    velocidad = SerialBT.read();
    angulo = SerialBT.read();
    jaja = SerialBT.read();
    angulo -= 88;
    direccion -= 272;
    //Serial.print("\n");

    executecommand(direccion, velocidad, angulo);
  }
}
