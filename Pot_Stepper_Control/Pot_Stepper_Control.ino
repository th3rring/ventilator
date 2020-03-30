
/*
Stepper Motor Control - speed control

This program drives a unipolar or bipolar stepper motor.
The motor is attached to digital pins 8 - 11 of the Arduino.
A potentiometer is connected to analog input 0.

The motor will rotate in a clockwise direction. The higher the potentiometer value,
the faster the motor speed. Because setSpeed() sets the delay between steps,
you may notice the motor is less responsive to changes in the sensor value at
low speeds.

Created 30 Nov. 2009
Modified 28 Oct 2010
by Tom Igoe

Port to Seeed Motor Shield
by Loovee 14 Mar, 2016

*/

#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor


// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 11, 12, 13);

int stepCount = 0;  // number of steps the motor has taken

int dead = 170;
int total = 1023;
int first = (total-dead)/2;
int second = (total+dead)/2;
int speed = 0;
int rev = 1;


void step(int steps)
{
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  myStepper.step(steps);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
}

void setup() {
  // nothing to do inside the setupseeed
}

void loop() {
  int pot = analogRead(A0);

  if (pot < first) {
    // Map speed
    speed = map(pot, 0, first, 100, 0);

    // Set direction to clockwise
    rev = 1;
  } else if (pot > second) {
    // Map speed
    speed = map(pot, second, total - 1, 0, 100);

    // Set direction to counterclockwise
    rev = -1;
  } else {
    speed = 0;
  }



  
  if (speed > 0) {
      myStepper.setSpeed(speed);
      // step 1/100 of a revolution:
      step(rev * stepsPerRevolution/100);
  }
}
