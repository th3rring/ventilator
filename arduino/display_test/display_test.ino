#include "nhd_0420d3z.h"
#include "Encoder.h"
#include "encodermanager.h"
#include "buttonmanager.h"
#include "ventsettings.h"

NhdDisplay display(3);
Encoder enc(5,6);
EncoderManager man(&enc, 4);
ButtonManager encoder_button(7, true);
ButtonManager stop_button(11, false);

VentSettings vs = {'X', 12, 1, 3, 500, 0, 0, 0, 0}; 

long pos = -999;
int row = 0;
int old_row = 0;

void setup()
{
  Serial.begin(9600);
  display.begin(9600);
  display.clearDisplay();
  display.setCursor(1,0);
  display.print("Hello world!");
  display.setCursor(1,1);
  display.print("Display working!");
  display.setCursor(1,2);
  int test = 40;
  char arr[100];
  sprintf(arr, "Number %i", test);
  display.print(arr);
  display.setCursor(1,3);
  display.print(String(vs.tidal_volume));
  
  display.setCursor(0,0);
  display.print(">");

  man.start();
}

void loop()
{
  man.poll();
  encoder_button.poll();
  stop_button.poll();

  int pos = man.getSelection();
  writeCursor(pos);

  if (encoder_button.getButtonState()) {
    Serial.println("encoder pressed!"); 
  }
  if (stop_button.getButtonState()) {
    Serial.println("stop pressed!"); 
  }

}

void writeCursor(int row) {
  if (row != old_row) {
    display.setCursor(0,old_row);
    /*display.print("");*/
    display.remove();

    display.setCursor(0,row);
    display.print(">");
    old_row = row;
  }
}
