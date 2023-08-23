#include <Arduino.h>

//Pin Sensor Sharp
const int pin_sharp = 34;
int analog_sharp;
int analog_sharp_acumulate;
int prom = 0;
//Pin Buttom
const int pin_buttom = 23;
int buttom_actived;

//Brayan vago :u
void setup() {
    pinMode(pin_sharp,INPUT);
    pinMode(pin_buttom,INPUT);
    Serial.begin(9600);
}

void loop(){
    buttom_actived = digitalRead(pin_buttom);
    Serial.print("Buttom is actived: ");
    Serial.println(buttom_actived);

    if (buttom_actived == 0){
      for (int i = 1; i<=100; i++){
        analog_sharp = analogRead(pin_sharp);
        analog_sharp_acumulate += analog_sharp;
        delay(60);
        Serial.print("Sharp: ");
        Serial.println(analog_sharp);
        }
    prom = (analog_sharp_acumulate)/100;
    }
    Serial.print("Promedio: ");
    Serial.println(prom);
    delay(5000);
}