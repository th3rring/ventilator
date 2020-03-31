#include <Wire.h>
#include <Servo.h>
#include <trajectory.h>

Servo servo;

int* traj_pos = 0;
int length = 0;

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  /*Wire.onReceive(recieveTraj); // register event*/
  Serial.begin(115200);           // start serial for output

  // Attach servo
  servo.attach(9);
}

void loop() {
  /*if (length != 0){*/
    /*Serial.println("--Recieved--");*/
    /*for (int i = 0; i < length; i++) {*/
      /*Serial.println(*(traj_pos+i));*/
    /*}*/
    /*delay(10000);*/
  /*}*/
  /*delay(10);*/
  if(Serial.available()>0) {
      length = Serial.parseInt();
      String test[length];

      int num_packets = Serial.parseInt();
      int per_packet = Serial.parseInt();

      for (int i = 0; i < num_packets; i++){
        for(int j = 0; j < per_packet; j++){

        
        }
      
      }



      /*Serial.println(length);*/
      traj_pos = new int[length];

      for (int i = 0; i < length; i++) {
        /**(traj_pos+i) = Serial.parseInt();*/
        test[i] = Serial.readStringUntil('\n');
      }

      delay(100);
      for (int i = 0; i < length; i++) {
        Serial.println(test[i]);
        delay(10);
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
  char mode = Wire.read();

  if (mode == 'l'){
  /*Serial.println("loading...");*/
  if(Serial.available()>0) {
      length = Serial.parseInt();
      /*Serial.println(length);*/
      traj_pos = new int[length];

      String data = Serial.readStringUntil('\n');
      Serial.println(data);
      String test[100];
      for (int i = 0; i < 100; i++) {
        /**(traj_pos+i) = Serial.parseInt();*/
        test[i] = Serial.readStringUntil('\n');
      }

      delay(100);
      for (int i = 0; i < 100; i++) {
        Serial.println(test[i]);
        delay(10);
      }


   }
  
  
  }
  
}
