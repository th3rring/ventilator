#include "panel.h"

NhdDisplay display(3);
Encoder enc(5,6);
ButtonManager encoder_button(7, true);
ButtonManager stop_button(11, false);

// Default settings
VentSettings vs = {'X', 12, 1, 3, 500, 0, 0, 0, 0}; 

// String params
String* splash_text = new String[4];


String* warning_text = new String[4];
SplashPanel* splash_ptr;
SplashPanel* warning_ptr;
EditPanel* start_ptr;
EditPanel* apply_ptr;
RunningPanel* run_ptr;
PausePanel* pause_ptr;

Panel* cur_panel;

void setup()
{
  Serial.begin(9600);
  display.begin(9600);
  display.clearDisplay();

  // Init slash text.
  splash_text[0] = "";
  splash_text[1] = "       Apollo";
  splash_text[2] = "        BVM";
  splash_text[3] = "";

  //Init warning text.
  warning_text[0] = "      WARNING: ";
  warning_text[1] = "      USE ADULT ";
  warning_text[2] = "        SIZED";
  warning_text[3] = "         BVM ";

  // Init panels.
  start_ptr = new EditPanel(&display, &enc, &encoder_button, &stop_button, &vs, "Confirm & Run?", &run_ptr, &pause_ptr);
  warning_ptr = new SplashPanel(&display, &enc, &encoder_button, &stop_button, &vs, warning_text, 2000, &start_ptr);
  splash_ptr = new SplashPanel(&display, &enc, &encoder_button, &stop_button, &vs, splash_text, 2000, &warning_ptr);
  apply_ptr = new EditPanel(&display, &enc, &encoder_button, &stop_button, &vs, "Apply Changes?", &run_ptr, &pause_ptr);
  run_ptr = new RunningPanel(&display, &enc, &encoder_button, &stop_button, &vs, &apply_ptr, &run_ptr);
  pause_ptr = new PausePanel(&display, &enc, &encoder_button, &stop_button, &vs, &start_ptr, &run_ptr);

  delay(500);

  // Set current panel to splash.
  cur_panel = splash_ptr;
  cur_panel->start();

}

void loop()
{
  encoder_button.poll();
  stop_button.poll();

  Serial.println(encoder_button.getButtonState());
  Serial.println(stop_button.getButtonState());

  Panel* new_panel = cur_panel->update();

  if (new_panel != 0) {
    cur_panel = new_panel;
    cur_panel->start();
  }

}

