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

  if (traj_pos != 0){
    delete [] traj_pos;
  }

  traj_pos = new uint8_t[num_entries/2];

  if (traj_times != 0){
    delete [] traj_times;
  }

  traj_times = new uint8_t[num_entries/2];
  
  for (int i = 0; i < num_entries/2; i++){
    traj_pos[i] = Wire.read();
    traj_times[i] = Wire.read();
  }

  /*traj = new Trajectory(traj_pos, traj_times);*/

  Serial.print(sizeof(traj_pos));

  Serial.print(" howMany: ");
  Serial.println(num_entries);
}

void moveTo(int pos, int ms) {
  
}

void followTraj() {
  //Start by 0ing the servo?
}
