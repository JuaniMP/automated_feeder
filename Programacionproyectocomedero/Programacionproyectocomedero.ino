#include <Ultrasonic.h>
#include <TimeLib.h>

int IN1 = 2;    // IN1 del L298N conectado al pin digital 2
int IN2 = 3;    // IN2 del L298N conectado al pin digital 3
int ENA = 5;    // ENA del L298N conectado al pin digital 5

const int trigPin = 6;    // Pin de disparo del sensor HC-SR04
const int echoPin = 7;    // Pin de eco del sensor HC-SR04

Ultrasonic ultrasonic(trigPin, echoPin);  // Creamos una instancia de la clase Ultrasonic

void setup() {
  pinMode(IN1, OUTPUT);   // Configura IN1 como salida
  pinMode(IN2, OUTPUT);   // Configura IN2 como salida
  pinMode(ENA, OUTPUT);   // Configura ENA como salida

  setTime(20, 22, 0, 15, 10, 2023); // Establece la fecha y hora actual (8:22 PM en GMT)
}

void loop() {
  // Obtiene la distancia del sensor HC-SR04 en centímetros
  long distance = ultrasonic.read();
  int currentHour = hour();
  unsigned long elapsedTime = millis();

  currentHour = (currentHour - 5 + 24) % 24; // Convertir a la zona horaria de Colombia (GMT-5)

  if (currentHour >= 8 || currentHour < 20) {
    if (distance <= 5 || elapsedTime <= 200) {  // Si la distancia es menor o igual a 5 centímetros y han pasado menos de 200 milisegundos
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 255);
    }  
    else if (distance > 5 || distance <= 10 || elapsedTime > 200 || elapsedTime <= 700) {  // Si la distancia es mayor que 5 cm y menor o igual a 10 cm y han pasado entre 200 y 700 milisegundos
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(ENA, 255);
    }  
    else if (distance > 10 || elapsedTime > 700) {  // Si la distancia es mayor a 10 cm y han pasado más de 700 milisegundos
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 0);
    }  
    else {  // Si no se cumplen las condiciones anteriores, apaga el motor
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 0);
    }
  } 
  else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);
  }
}

