/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

#define S_TO_MS 100

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

// Respitory parameters are in seconds
float hold = 0.2;
float respitory_rate = 15;

// Timing parameters, in seconds
float t_tot = 4;
float t_in = 0;
float t_out = 0;

// Ratio
float ie_ratio = 1/3;

// Operating parameters
int delta_t = 20;
int start = 2490;
int stop = 510;
int delta_t_scale = 1000/delta_t;


void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  /*t_tot = 60 / respitory_rate;*/
  t_out = (t_tot - hold) / (ie_ratio + 1);
  t_in = ie_ratio * t_out;
  /*Serial.print("t_out: ");*/
  /*Serial.print(t_out);*/
  /*Serial.print(" t_in: ");*/
  /*Serial.print(t_in);*/
}

void loop() {

  for (int t = 0; t <= t_in * delta_t_scale; t++) {
    pos = start - ((start-stop)/(t_in*delta_t_scale)) * t;
    Serial.println(pos);
    myservo.writeMicroseconds(pos);
    delay(delta_t);
  }

  delay(hold * 1000);

  for (int t = 0; t < t_out * delta_t_scale; t++) {
    pos = stop + ((start-stop)/(t_out * delta_t_scale)) * t;
    Serial.println(pos);
    myservo.writeMicroseconds(pos);
    delay(delta_t);
  }
  
  /*for (pos = start; pos >= start - period; pos -= 10) { // goes from 180 degrees to 0 degrees*/
    /*myservo.writeMicroseconds(pos);              // tell servo to go to position in variable 'pos'*/
    /*delay(15);*/
  /*}*/
  /*for (pos = start - period; pos <= start; pos += 10) { // goes from 0 degrees to 180 degrees*/
    /*myservo.writeMicroseconds(pos);              // tell servo to go to position in variable 'pos'*/
    /*delay(15);*/
  /*}*/

  /*myservo.writeMicroseconds(1500+period);*/
    /*delay(start);                       // waits 15ms for the servo to reach the position*/
    /*myservo.writeMicroseconds(1500-period);*/
    /*delay(start);                       // waits 15ms for the servo to reach the position*/
}
