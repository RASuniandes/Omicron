// Incluimos las librerías necesarias
#include <PID_v1.h>
#include <QTRSensors.h>

// Definir pines de los sensores
#define SJF1 A0
#define SJF2 A1
#define SJF3 A2
#define SJF4 A3
#define SJF5 A4

#define QTR_A0 A5
#define QTR_A1 A6

// Pines de los motores
#define MOTOR_A_FORWARD 3
#define MOTOR_A_BACKWARD 4
#define MOTOR_B_FORWARD 5
#define MOTOR_B_BACKWARD 6

// Variables PID
double Setpoint, Input, Output;
double Kp = 2.0, Ki = 5.0, Kd = 1.0; // Ajustes iniciales PID
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

// Configurar QTR
QTRSensorsAnalog qtr((unsigned char[]) {QTR_A0, QTR_A1}, 2);
unsigned int sensorValues[2];

// Variables de estado
int sensorJF[5];
int umbralJF = 600; // Valor umbral de detección de objetos
int umbralQTR = 200; // Umbral para borde del ring

void setup() {
  // Inicializamos pines de los motores
  pinMode(MOTOR_A_FORWARD, OUTPUT);
  pinMode(MOTOR_A_BACKWARD, OUTPUT);
  pinMode(MOTOR_B_FORWARD, OUTPUT);
  pinMode(MOTOR_B_BACKWARD, OUTPUT);

  // Inicializamos el PID
  Setpoint = 0;  // El setpoint es el punto de equilibrio del robot
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-255, 255); // Limitar salida para los motores

  Serial.begin(9600);
}

void loop() {
  leerSensores();

  // Sumamos las lecturas de los sensores frontales (JF40S)
  int sumaSensores = sensorJF[0] + sensorJF[1] + sensorJF[3] + sensorJF[4];
  
  // Asumimos que el robot debe mantenerse en el centro (equilibrio)
  Input = sensorJF[2] - (sumaSensores / 4); // Error: diferencia entre el sensor central y los demás
  myPID.Compute(); // Calculamos la salida PID

  // Ajustar motores basado en el PID
  ajustarMotores(Output);

  // Detectar borde del ring con sensores QTR
  qtr.read(sensorValues);

  if (sensorValues[0] < umbralQTR || sensorValues[1] < umbralQTR) {
    // Si detectamos el borde, retrocedemos y giramos
    girarRapido();
  }
}

// Leer sensores JF40S
void leerSensores() {
  sensorJF[0] = analogRead(SJF1);
  sensorJF[1] = analogRead(SJF2);
  sensorJF[2] = analogRead(SJF3);
  sensorJF[3] = analogRead(SJF4);
  sensorJF[4] = analogRead(SJF5);
}

// Ajuste de los motores según la salida PID
void ajustarMotores(double ajuste) {
  int velocidadBase = 150; // Velocidad base de los motores
  int motorA = velocidadBase + ajuste;
  int motorB = velocidadBase - ajuste;

  if (motorA > 0) {
    analogWrite(MOTOR_A_FORWARD, motorA);
    analogWrite(MOTOR_A_BACKWARD, 0);
  } else {
    analogWrite(MOTOR_A_FORWARD, 0);
    analogWrite(MOTOR_A_BACKWARD, -motorA);
  }

  if (motorB > 0) {
    analogWrite(MOTOR_B_FORWARD, motorB);
    analogWrite(MOTOR_B_BACKWARD, 0);
  } else {
    analogWrite(MOTOR_B_FORWARD, 0);
    analogWrite(MOTOR_B_BACKWARD, -motorB);
  }
}

// Acción de giro rápido cuando detecta el borde
void girarRapido() {
  analogWrite(MOTOR_A_FORWARD, 0);
  analogWrite(MOTOR_A_BACKWARD, 255);
  analogWrite(MOTOR_B_FORWARD, 255);
  analogWrite(MOTOR_B_BACKWARD, 0);
  delay(500);  // Girar por medio segundo
}
