# 1 "/home/therring/Workspace/ventilator/Stepper_Alternator/Stepper_Alternator.ino"
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

# 15 "/home/therring/Workspace/ventilator/Stepper_Alternator/Stepper_Alternator.ino" 2

// change this to the number of steps on your motor


// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(200, 8, 11, 12, 13);

// the previous reading from the analog input
int previous = 0;
int offset = 0;

void step(int steps)
{
  digitalWrite(9, 0x1);
  digitalWrite(10, 0x1);
  stepper.step(steps);
  digitalWrite(9, 0x0);
  digitalWrite(10, 0x0);
}

void setup()
{
  // set the speed of the motor to 30 RPMs
  pinMode(9, 0x1);
  pinMode(10, 0x1);
  digitalWrite(9, 0x0);
  digitalWrite(10, 0x0);
  stepper.setSpeed(40);
  Serial.begin(9600);
  offset = analogRead(0);

}

void loop()
{
  // get the sensor value
  int pot = analogRead(0);
  int pot_steps = map(pot - offset, 0, 1023, 0, 200);
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
