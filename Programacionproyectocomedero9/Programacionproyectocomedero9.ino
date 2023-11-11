#include <TimeLib.h>

int IN1 = 2;
int IN2 = 3;
int ENA = 5;

char incomingValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  setTime(20, 22, 0, 15, 10, 2023);
}

void loop() {
  if (Serial.available() > 0) {
    incomingValue = Serial.read();
    Serial.print(incomingValue);
    Serial.print("\n");

    if (incomingValue == '1') {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 255);
    }
    else if (incomingValue == '0') {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 0);
    }
  }

  int currentHour = hour();
  unsigned long elapsedTime = millis();

  currentHour = (currentHour - 5 + 24) % 24;

  if (currentHour >= 8 || currentHour < 20) {
    if (elapsedTime <= 200) {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 255);
    }
    else if (elapsedTime > 200 && elapsedTime <= 700) {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(ENA, 255);
    }
    else if (elapsedTime > 700) {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 0);
    }
    else {
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
