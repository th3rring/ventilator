#include <Wire.h>

#define button_pin 7

bool wave = true;

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  pinMode(button_pin, INPUT);
  Serial.begin(9600);
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
  Wire.write('L');
  if (wave) {
  Wire.write(12);
  wave = false;
  } else {
  Wire.write(15); 
  wave = true;
  }
  Wire.write(50);

  /*Wire.write(String(traj_ptr->getLength()));*/
  /*Wire.write(",");*/
  /*Wire.write(String(traj_ptr->getDeltaTime()));*/
  /*Wire.write('l');*/


  /*for (int i = 0; i < traj_ptr->getLength(); i++){*/
    /*Wire.write(",");*/
    /*Wire.write(String(traj_ptr->nextStep()));*/
  /*}*/

  Wire.endTransmission();    // stop transmitting
}
