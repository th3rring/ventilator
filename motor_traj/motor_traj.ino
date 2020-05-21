#include <SparkFun_TB6612.h>
#include <Encoder.h>
#include <PIDController.h>
#include <trajfactory.h>

#define AIN1 5
#define AIN2 4
#define PWMA 11
#define STBY 9

const int offsetA = -1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

Encoder myEnc(2, 3);

PIDController pid;

TrajFactory tf = TrajFactory();
Trajectory* traj_ptr = 0;

int delta_t = 10;

void setup() {
  Serial.begin(9600);
  Serial.println("Encoder Motor");

  pid.begin();
  pid.tune(1,0.5,0);
  pid.limit(-255,255);

  traj_ptr = tf.build(15, 0.33, 20000, 0, delta_t);
}

double oldPosition  = -999;

double sp = -10000;

double outSpeed;


void loop() {

moveTo(traj_ptr->nextStep());

}


void moveTo(int pos) {

pid.setpoint(pos);

  
unsigned long startedWaiting = millis();
while(millis() - startedWaiting <= delta_t) {

  double newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
  }

  double set = pid.compute(oldPosition);
  Serial.println(oldPosition);

  motor1.drive(set);
}


  
}
