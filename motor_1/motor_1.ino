#include <SparkFun_TB6612.h>
#include <Encoder.h>
#include <AutoPID.h>


#define AIN1 11
#define AIN2 4
#define PWMA 5
#define STBY 9

const int offsetA = 1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

Encoder myEnc(2, 3);


void setup() {
  Serial.begin(9600);
  Serial.println("Encoder Motor");
}

double oldPosition  = -999;

double sp = -10000;

double outSpeed;

AutoPID myPID(&oldPosition, &sp, &outSpeed, -255.0, 255.0, 0.06, 0.00, 0);


void loop() {
  // put your main code here, to run repeatedly:
    double newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
//    Serial.print(newPosition);
//    Serial.print(" ");
    Serial.println(outSpeed);
  }

myPID.run();

motor1.drive(outSpeed);

}
