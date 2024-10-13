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


//engines
Motor motor_a(26, 27);
Motor motor_b(33, 32);


//Starter 
Starter start(21, 14);


//Comentarios
bool comments = true;


//Otras Variables auxiliares
int _numSensors = 5; //cantidad de sensores usados
int sensorValues[5];

// Qtr - Parámetros
int time_backward = 200; // Constante de tiempo reversa  total
int time_backward_twist = 180; // constante de tiempo del giro por lo tato menor a time_backward
int velocity_backward = 240;

int motorA_velocity = 0, motorB_velocity = 0;

//PID
int reference = 255;
int sensibility = 140;
int attack_velocity = 255;

float Kp = 3, Ki = 0, Kd = 0;

Pid pid(Kp, Ki, Kd, 20, reference, _numSensors);

//Estrategias
int pinButton = 12;
int strategy_number = 0;

/**
 * @brief Obtiene los valores de los sensores.
 *
 * Esta función lee los valores de los sensores s1, s2, s3, s4 y s5 y los guarda en un arreglo.
 *
 * @return Puntero al arreglo de valores de los sensores.
 */
int* getSharpValues() {

  sensorValues[0] = s1.readValue();
  sensorValues[1] = s2.readValue();
  sensorValues[2] = s3.readValue();
  sensorValues[3] = s4.readValue();
  sensorValues[4] = s5.readValue();
  return sensorValues;
}


/**
 * @brief Configura la velocidad de los engines.
 *
 * @param speed_m_left Velocidad del motor izquierdo.
 * @param speed_m_right Velocidad del motor derecho.
 */
void engines(int speed_m_left, int speed_m_right) {
  motor_a.setSpeed(speed_m_left);
  motor_b.setSpeed(speed_m_right);
}


void dynamic_brake() {
  motor_a.brake();
  motor_b.brake();
}


/**
 * Muestra los valores de los sensores.
 * Imprime los valores de los sensores qtr_lef, qtr_right, s1, s2, s3, s4, s5, Starter y Stop en el monitor serie.
 */
void show_sensors() {
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


/**
 * Función que realiza un giro en reversa según la dirección especificada.
 * 
 * @param direction Dirección del giro en reversa. Si es igual a 1, se realiza un giro hacia la izquierda (qtr_left).
 *                  Si es igual a 0, se realiza un giro hacia la derecha.
 *                  Si es diferente de 0 y 1, se realiza un giro hacia la izquierda (qtr_left) por defecto.
 */
void Twist_reverse(int direction) {

  // si direction es igual 0 es qtr_left
  if (direction == 1) {

    motorA_velocity = velocity_backward;
    motorB_velocity = -velocity_backward;

  }
  else if (direction == 0) {

    motorA_velocity = -velocity_backward;
    motorB_velocity = velocity_backward;

  }
  else {
    motorA_velocity = velocity_backward;
    motorB_velocity = -velocity_backward;
  }

  // Código para el primer intervalo de reversa
  engines(-velocity_backward, -velocity_backward);
  delay(time_backward);

  // Código para el intervalo restante de giro en segundos
  engines(motorA_velocity, motorB_velocity);
  delay(time_backward_twist);

  engines(0, 0);
  delayMicroseconds(100);
}


/**
 * Función que controla el comportamiento del robot cuando se encuentra en la etapa de ingreso.
 * 
 * @param qtr_left_value Valor del sensor izquierdo de línea.
 * @param qtr_right_value Valor del sensor derecho de línea.
 */

void getIn(int qtr_left_value, int qtr_right_value) {

  // dynamic_brake();
  engines(-20, -20);

  delay(300);

  if (qtr_right_value == 0 && qtr_left_value == 1) {
      
    Twist_reverse(0);

  }
  else if (qtr_right_value == 1 && qtr_left_value == 0) {

    Twist_reverse(1);

  }
  else if (qtr_right_value == 0 && qtr_left_value == 0) {

    Twist_reverse(1);

  }
}


/**
 * @brief Función que controla los frenos del contorno.
 * 
 * Esta función ajusta los frenos del contorno de acuerdo a la posición recibida como parámetro.
 * Si la posición es menor o igual a cero, se ajustan los engines con la posición menos z y la referencia.
 * Si la posición es mayor o igual a 40, se ajustan los engines con la referencia y la posición negativa menos z.
 * 
 * @param position La posición del contorno.
 */
void contour_brakes(int position) {

  if (position <= -20) {
    engines(sensibility, -sensibility);
  }
  else if (position >= 20) {
    engines(-sensibility, sensibility);
  }

}


/**
 * Realiza el seguimiento del objeto en movimiento.
 * Calcula el error de posición utilizando los valores obtenidos de los sensores.
 * Aplica el control PID para obtener la salida de control.
 * Ajusta los engines según la salida de control obtenida.
 * Aplica frenos de contorno según la posición del objeto.
 */
void tracking() {
  int* values = getSharpValues();
  int position = pid.calculateError(values);
  int control_output = pid.traking(position);


  if (control_output < 0) {
    engines( -control_output + sensibility, sensibility );
  }
  else if (control_output > 0) {
    engines(sensibility, control_output + sensibility);
  }
  else if (control_output == 0) {
    engines(attack_velocity, attack_velocity);
  }

  contour_brakes(position);
}


/**
 * Función que ataca al oponente.
 * 
 * Esta función verifica los valores de los sensores qtr_left y qtr_right.
 * Si ambos sensores tienen un valor de 1, se llama a la función tracking().
 * En caso contrario, se llama a la función getIn() pasando los valores de los sensores como argumentos.
 */
void attack() {
  
  qtr_left_value = qtr_left.value();
  qtr_right_value = qtr_right.value();

  if (qtr_left_value == 1 && qtr_right_value == 1) {
    tracking();
  }
  else {
    getIn(qtr_left_value, qtr_right_value);
  }

}

bool enemy_on_line() {
  return s1.readValue() == 0 || s2.readValue() == 0 || s3.readValue() == 0 || s4.readValue() == 0 || s5.readValue() == 0;
}
/**
 * Ejecuta una estrategia específica según el valor de la variable 'strategy'.
 * 
 * @param strategy El valor de la estrategia a ejecutar.
 */
void strategy(int strategy) {

  switch (strategy)
  {
  case 0:
    while (!enemy_on_line()) {

      engines(50, 50);
      qtr_left_value = qtr_left.value();
      qtr_right_value = qtr_right.value();

      if (qtr_left_value == 0 || qtr_right_value == 0) {
        getIn(qtr_left_value, qtr_right_value);
      }
    }

    attack();
    break;
  
  case 1:
    while (!enemy_on_line()) {

        engines(60, 60);
        delay(100);
        engines(0, 0);
        qtr_left_value = qtr_left.value();
        qtr_right_value = qtr_right.value();

        if (qtr_left_value == 0 || qtr_right_value == 0) {
          getIn(qtr_left_value, qtr_right_value);
        }

    }
    attack();
    break;

  case 2:
    while (!enemy_on_line()) {

      engines(120, 100);
      delay(200);
      engines(120, 120);
      delay(200);
      engines(100, 120);
      delay(200);

      qtr_left_value = qtr_left.value();
      qtr_right_value = qtr_right.value();

      if (qtr_left_value == 0 || qtr_right_value == 0) {
        getIn(qtr_left_value, qtr_right_value);
      }
    }

    attack();

  case 3:

    while (!enemy_on_line()) {

      qtr_left_value = qtr_left.value();
      qtr_right_value = qtr_right.value();

      if (qtr_left_value == 0 || qtr_right_value == 0) {
        getIn(qtr_left_value, qtr_right_value);
      }

    }

    attack();
  
  default:
    break;
  }
 
}



/**
 * @brief Configura el entorno inicial del programa.
 * 
 * Esta función se ejecuta una vez al inicio del programa y se utiliza para configurar
 * los pines y los dispositivos necesarios.
 */
void setup() {
  // put your setup code here, to run once:

  strategy_number = 0;
  pinMode(pinButton, INPUT);
  if (comments == true) {
    Serial.begin(9600);
  }

}


/**
 * @brief Función principal del programa que se ejecuta en un bucle infinito.
 * 
 * La función loop se encarga de controlar el flujo principal del programa. 
 * Verifica si se ha iniciado el juego y si todos los sensores están en estado bajo (0). 
 * En caso afirmativo, se ejecuta la estrategia correspondiente y se reinicia el juego. 
 * Si el juego no ha iniciado, se detienen los engines y se permite cambiar la estrategia 
 * utilizando un botón. 
 */
void loop() {

  if (start.getStart() == 1 && start.getStop() == 0) {

    strategy(strategy_number);
    
  } else {

    engines(0, 0);  
    strategy_number > 5 ? strategy_number = 0: strategy_number=strategy_number + digitalRead(pinButton);
    delay(300);
  }

  delayMicroseconds(100);
}