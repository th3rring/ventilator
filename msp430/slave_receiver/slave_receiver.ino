// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

#define led_pin 2

void setup()
{
  Wire.setModule(0);
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  pinMode(led_pin, OUTPUT);
}

void loop()
{
  /*flashNTimes(2);*/
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  int x = Wire.read();    // receive byte as an integer
  flashNTimes(x);
}

void flashNTimes(int n){
  for(int i = 0; i < n; ++i) { 
  digitalWrite(led_pin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(led_pin, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
  }
}
