#include <Wire.h>

#define button_pin 7

using uint = unsigned int;

bool wave = true;
bool on = true;

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

  /*if (on) {*/
  Wire.write('L');
  /*if (wave) {*/
  /*Wire.write(5);*/
  /*wave = false;*/
  /*} else {*/

  //Write RR
  Wire.write(12); 

  // Write inhale and exhale ratio
  Wire.write(1);
  Wire.write(3);

  // Write setpoint
  int setpoint = 1300;
  Wire.write(byte(setpoint >> 8));
  Wire.write(byte(setpoint & 0x00FF));

  //Wire delta_t
  Wire.write(20);

  // Write hold as seconds and 10s of ms.
  Wire.write(0);
  Wire.write(0);
  on = false;
  /*} else {*/
    /*Wire.write('X');*/
    /*on = true;*/
  /*}*/

  Wire.endTransmission();    // stop transmitting
}
