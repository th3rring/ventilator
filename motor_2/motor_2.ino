#include <SparkFun_TB6612.h>
#include <Encoder.h>
#include <PIDController.h>


#define AIN1 5
#define AIN2 4
#define PWMA 11
#define STBY 9

const int offsetA = -1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

Encoder myEnc(2, 3);

PIDController pid;



void setup() {
  Serial.begin(9600);
  Serial.println("Encoder Motor");

  pid.begin();
  pid.setpoint(30000);
  pid.tune(1,0.5,0);
  pid.limit(-255,255);
}

double oldPosition  = -999;

double sp = -10000;

double outSpeed;


void loop() {
  // put your main code here, to run repeatedly:
    double newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
//    Serial.println(newPosition);
  }

double set = pid.compute(oldPosition);
Serial.println(oldPosition);

// Position control likely not working due to power constraints on Arduino
motor1.drive(set);
delay(10);

}
