#include <Arduino.h>
#line 1 "/home/therring/Workspace/ventilator/Stepper_Alternator/Stepper_Alternator.ino"
/*
* MotorKnob
*
* A stepper motor follows the turns of a potentiometer
* (or other sensor) on analog input 0.
*
* Port to Seeed Motor Shield
* loovee@Mar 14, 2016
*
* http://www.arduino.cc/en/Reference/Stepper
* This example code is in the public domain.
*/

#include <Stepper.h>

// change this to the number of steps on your motor
#define STEPS 200

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 8, 11, 12, 13);

// the previous reading from the analog input
int previous = 0;
int offset = 0;

#line 28 "/home/therring/Workspace/ventilator/Stepper_Alternator/Stepper_Alternator.ino"
void step(int steps);
#line 37 "/home/therring/Workspace/ventilator/Stepper_Alternator/Stepper_Alternator.ino"
void setup();
#line 50 "/home/therring/Workspace/ventilator/Stepper_Alternator/Stepper_Alternator.ino"
void loop();
#line 28 "/home/therring/Workspace/ventilator/Stepper_Alternator/Stepper_Alternator.ino"
void step(int steps)
{
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  stepper.step(steps);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
}

void setup()
{
  // set the speed of the motor to 30 RPMs
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  stepper.setSpeed(40);
  Serial.begin(9600);
  offset = analogRead(0);

}

void loop()
{
  // get the sensor value
  int pot = analogRead(0);
  int pot_steps = map(pot - offset, 0, 1023, 0, STEPS);
  Serial.print("Pot: ");
  Serial.print(pot);
  Serial.print(", Pot Steps: ");
  Serial.print(pot_steps);
  Serial.print(", cur-prev: ");
  Serial.println(pot_steps - previous);

  // move a number of steps equal to the change in the
  // sensor reading
  //step(pot_steps - previous);
  step(100);
  step(-100);
  
  // remember the previous value of the sensor
  previous = pot_steps;
}

