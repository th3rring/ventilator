#include "nhd_0420d3z.h"
#include "Encoder.h"
#include "encodermanager.h"

NhdDisplay display(3);
Encoder enc(5,6);
EncoderManager man(&enc, 4);

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
  
  display.setCursor(0,0);
  display.print(">");

  man.start();
}

void loop()
{

  /*long new_pos = enc.read();*/
  /*if (new_pos != pos) {*/

    /*[>if (delta < 0) {<]*/
      /*[>row--;<]*/
    /*[>} else if (delta > 0) {<]*/
      /*[>row++;<]*/
    /*[>}<]*/

    /*[>if (row > 3) {<]*/
    /*[>row = 3;<]*/
    /*[>} else if (row < 0) {<]*/
    /*[>row = 0; <]*/
    /*[>}<]*/
    /*if (new_pos < 0){*/
      /*enc.write(0);*/
      /*new_pos = 0;*/
    /*} else if (new_pos > 16) {*/
      /*enc.write(16);*/
      /*new_pos = 16;*/
    /*}*/

    /*pos = new_pos;*/

    /*if (0 <= pos && pos < 4) {*/
      /*writeCursor(0);*/
    /*} else if (4 <= pos && pos < 8) {*/
      /*writeCursor(1);*/
    /*} else if (8 <= pos && pos < 12) {*/
      /*writeCursor(2);*/
    /*} else if (12 <= pos && pos < 16) {*/
      /*writeCursor(3);*/
    /*}*/



  /*}*/

  man.poll();

  int pos = man.getSelection();
  Serial.println(pos);
  writeCursor(pos);




}

void writeCursor(int row) {
  if (row != old_row) {
    Serial.print(old_row);
    Serial.print(" ");
    Serial.println(row);
    display.setCursor(0,old_row);
    /*display.print("");*/
    display.remove();

    display.setCursor(0,row);
    display.print(">");
    old_row = row;
  }
}
