#include "buttonmanager.h"

ButtonManager encoder_button(7, true);

void setup() {
  Serial.begin(9600);
}

void loop() {
  encoder_button.poll();

  /*Serial.println(encoder_button.getButtonState());*/
  int i = 9;
  char digit[2];
  sprintf(digit, "%02d", i);
  Serial.println(digit);

}
