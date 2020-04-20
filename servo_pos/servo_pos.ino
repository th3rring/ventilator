#include "Servo.h"


Servo s;
int setpoint = 500;

void setup() {
  Serial.begin(9600);
  s.attach(9);
}


void loop() {
  Serial.println(setpoint);
  s.writeMicroseconds(setpoint);
  delay(15);
  /*if (Serial.available()) {*/
    /*setpoint = Serial.read();*/
  /*}*/
}
