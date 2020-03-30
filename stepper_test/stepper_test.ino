#include <AccelStepper.h>

#define dirPin 2
#define stepPin 3
#define motorInterfaceType 1

#define start 60
#define STEPS 200

#define INHALE 1.5
#define EXHALE 3.5

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void setup()
{
  Serial.begin(9600);

  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(200);
  stepper.setAcceleration(100);
  //stepper.runToNewPosition(start);
  //stepper.setSpeed(50);
  // This is critical, smaller pulse widths cause drift.
  stepper.setMinPulseWidth(20);

  // Move to the start
  //stepper.runToNewPosition(start);
}

void loop()
{

  // get the sensor value
  //  int pot = analogRead(0);
  //  int pot_steps = map(pot, 0, 1023, 0, STEPS);
  int pot_steps = 800;
  //  Serial.print("Oscillating: ");
  //  Serial.println(pot_steps);

  //  stepper.setMaxSpeed(int(pot_steps/INHALE));

  stepper.runToNewPosition(start + pot_steps);

  //  stepper.setMaxSpeed(int(pot_steps/EXHALE));

  stepper.runToNewPosition(start);
  //  if (stepper.distanceToGo() == 0){
  //    stepper.moveTo(-stepper.currentPosition());
  //    Serial.println("Reversing!");
  //  }

  //  Serial.println(stepper.currentPosition());

  //  stepper.run();
}
