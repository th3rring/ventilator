#include <Wire.h>

#define button_pin 7

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  pinMode(button_pin, INPUT);
}

byte x = 0;
int button_state = 0;

// First entry is the rotary position
// Second entry is the time in 10s of miliseconds
byte traj[][2] = {{0,0},{90,250},{180,250}};

void loop() {
  button_state = digitalRead(button_pin);

    transmitTraj();
  if (button_state == LOW) {
  }

  delay(500);
}

void transmitTraj() {

  Wire.beginTransmission(8); // transmit to device #8

  for(int i = 0; i < sizeof(traj)/2; i++) {
  Wire.write(traj[i][0]);              // send first traj
  Wire.write(traj[i][1]);
  }

  Wire.endTransmission();    // stop transmitting
  
}
