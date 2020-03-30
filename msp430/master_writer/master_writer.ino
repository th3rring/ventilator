// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

#define led_pin 2

void setup()
{
  Wire.setModule(0);
  Wire.begin(); // join i2c bus (address optional for master)
  pinMode(led_pin, OUTPUT);
}

byte x = 2;

void loop()
{
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(x);              // sends one byte  
  /*Wire.endTransmission();    // stop transmitting*/

  delay(500);
  /*digitalWrite(led_pin, HIGH);   // turn the LED on (HIGH is the voltage level)*/
  /*delay(250);                       // wait for a second*/
  /*digitalWrite(led_pin, LOW);    // turn the LED off by making the voltage LOW*/
  /*delay(250);                       // wait for a second*/
}
