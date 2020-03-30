#include <Wire.h>
#include <Servo.h>
#include <trajectory.h>

using uint8_t = unsigned char;

Servo servo;

uint8_t* traj_pos = 0;
uint8_t* traj_times = 0;

Trajectory traj = Trajectory(traj_pos, traj_times);

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(recieveTraj); // register event
  Serial.begin(9600);           // start serial for output

  // Attach servo
  servo.attach(9);
}

void loop() {
  delay(10);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void recieveTraj(int num_entries) {

}
