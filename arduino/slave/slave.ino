#include <Wire.h>
#include <Servo.h>
#include <trajfactory.h>

#define SERVO_MIN 2490
#define SERVO_MAX 510

TrajFactory tf = TrajFactory();
Trajectory* traj_ptr = 0;
Trajectory* temp  = 0;

int rr;
int delta_t;
float ie;
int setpoint;
float hold;

Servo servo;

char state;

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(recieveTraj); // register event
  /*Serial.begin(115200);           // start serial for output*/
  Serial.begin(9600);           // start serial for output

  // Attach servo
  servo.attach(9);
  state = 'X';
}

void loop() {
  /*if(Serial.available()>0) {*/
      /*length = Serial.parseInt();*/
      /*String test[length];*/

      /*int num_packets = Serial.parseInt();*/
      /*int per_packet = Serial.parseInt();*/
   /*}*/
  /*Serial.println(mode);*/

  switch (state) {
    case 'O': 
      moveTo(traj_ptr->nextStep(), traj_ptr->getDeltaTime());
      break;
    case 'X':
      stop();
      break;
    case 'L':

      // Stop motion.
      stop();

      // If assigned ptr, delete contents
      if (traj_ptr != 0) {
        delete traj_ptr;
      }

      // Build new trajectory
      traj_ptr = tf.build(rr, ie, setpoint, hold, delta_t);

      // Set device on.
      state = 'O';
      break;

  }

  if (state == 'O') {
  }
}

void moveTo(int pos, int delta_t){
  Serial.println(SERVO_MIN-pos);
  /*servo.writeMicroseconds(2490-pos);*/
  delay(delta_t);
}

void stop(){
      if (traj_ptr != 0) {
        while (traj_ptr->getCurrentStep() != 0) {
          moveTo(traj_ptr->nextStep(), traj_ptr->getDeltaTime());
        }
      }
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void recieveTraj(int num_entries) {
  /*String s = "";*/
  /*while (1 < Wire.available()) { // loop through all but the last*/
    /*char c = Wire.read(); // receive byte as a character*/
  /*}*/
  state = Wire.read();

  switch (state) {
    case 'X':
      state = 'X';
      break;
    case 'O':
      state = 'O';
      break;
    case 'L':
      // Load new params
      rr = Wire.read();

      byte inhale = Wire.read();
      byte exhale = Wire.read();
      ie = float(inhale) / exhale;

      byte high = Wire.read();
      byte low = Wire.read();
      setpoint = (high << 8) | low;

      delta_t = Wire.read();

      byte hold_s = Wire.read();
      byte hold_dec = Wire.read();
      hold = hold_s + hold_dec/100.0;

      break;
  }
}
