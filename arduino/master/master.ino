#include <Wire.h>
#include <trajfactory.h>

#define button_pin 7

TrajFactory tf = TrajFactory();
Trajectory* traj_ptr;

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  traj_ptr = tf.build(12, 0.5, 2000, 1, 10);
  pinMode(button_pin, INPUT);
}

int button_state = 0;

// First entry is the rotary position
// Second entry is the time in 10s of miliseconds

void loop() {
  button_state = digitalRead(button_pin);

  if (button_state == LOW) {
    transmitTraj();
  }

  delay(500);
}

void transmitTraj() {

  Wire.beginTransmission(8); // transmit to device #8

  Wire.write(String(traj_ptr->getLength()));
  Wire.write(",");
  Wire.write(String(traj_ptr->getDeltaTime()));


  for (int i = 0; i < traj_ptr->getLength(); i++){
    Wire.write(",");
    Wire.write(String(traj_ptr->nextStep()));
  }

  Wire.endTransmission();    // stop transmitting
  
}
