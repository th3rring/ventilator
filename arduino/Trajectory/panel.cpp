#include "panel.h"


Panel::Panel(NhdDisplay* disp_ptr, Encoder* encoder_ptr, ButtonManager* em_button_ptr, ButtonManager* stop_button_ptr, VentSettings* vs_ptr, String text[4]) :
  _disp_ptr(disp_ptr),
  _encoder_ptr(encoder_ptr),
  _em_button_ptr(em_button_ptr),
  _stop_button_ptr(stop_button_ptr),
  _vs_ptr(vs_ptr),
  _text(text) {}

SplashPanel::SplashPanel(NhdDisplay* disp_ptr, Encoder* encoder_ptr, ButtonManager* em_button_ptr, ButtonManager* stop_button_ptr, VentSettings* vs_ptr, String text[4], int display_time, Panel* next_ptr) :
  Panel{disp_ptr, encoder_ptr, em_button_ptr, stop_button_ptr, vs_ptr, text},
  _next_ptr(next_ptr) {}

void SplashPanel::start() {
  _disp_ptr->clearDisplay();
  for (int i = 0; i < 4; i++) {
    _disp_ptr->setCursor(i, 0);
    _disp_ptr->print(_text[i]);
  }
}

Panel* SplashPanel::update() {
  // Write text from first col.
  delay(_display_time);
  return _next_ptr;
}

EditPanel::EditPanel(NhdDisplay* disp_ptr, Encoder* encoder_ptr, ButtonManager* em_button_ptr, ButtonManager* stop_button_ptr, VentSettings* vs_ptr, String text[4], Panel* run_panel_ptr, Panel* stop_panel_ptr) :
  Panel{disp_ptr, encoder_ptr, em_button_ptr, stop_button_ptr, vs_ptr, text},
  _run_panel_ptr(run_panel_ptr),
  _stop_panel_ptr(stop_panel_ptr) {
    _em = EncoderManager(encoder_ptr, 4);
  }

void SplashPanel::start() {
  _disp_ptr->clearDisplay();
  for (int i = 0; i < 4; i++) {
    _disp_ptr->setCursor(i, 0);
    _disp_ptr->print(_text[i]);
  }
}

  Panel* EditPanel::update() {
  
  
  
  }
