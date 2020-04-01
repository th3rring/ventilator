#include "panel.h"


Panel::Panel(NhdDisplay* disp_ptr, Encoder* encoder_ptr, ButtonManager* em_button_ptr, ButtonManager* stop_button_ptr, VentSettings* vs_ptr) :
  _disp_ptr(disp_ptr),
  _encoder_ptr(encoder_ptr),
  _em_button_ptr(em_button_ptr),
  _stop_button_ptr(stop_button_ptr),
  _vs_ptr(vs_ptr) {}

SplashPanel::SplashPanel(NhdDisplay* disp_ptr, Encoder* encoder_ptr, ButtonManager* em_button_ptr, ButtonManager* stop_button_ptr, VentSettings* vs_ptr, String text[4], int display_time, Panel* next_ptr) :
  Panel{disp_ptr, encoder_ptr, em_button_ptr, stop_button_ptr, vs_ptr},
  _next_ptr(next_ptr) {}

void SplashPanel::start() {

  // Clear display.
  _disp_ptr->clearDisplay();

  // Display each line.
  for (int i = 0; i < 4; i++) {
    _disp_ptr->setCursor(i, 0);
    _disp_ptr->print(_text[i]);
  }
}

Panel* SplashPanel::update() {

  // Wait for time and then pass next panel.
  delay(_display_time);
  return _next_ptr;
}

EditPanel::EditPanel(NhdDisplay* disp_ptr, Encoder* encoder_ptr, ButtonManager* em_button_ptr, ButtonManager* stop_button_ptr, VentSettings* vs_ptr, String top_text, Panel* run_panel_ptr, Panel* stop_panel_ptr) :
  Panel{disp_ptr, encoder_ptr, em_button_ptr, stop_button_ptr, vs_ptr},
  _run_panel_ptr(run_panel_ptr),
  _stop_panel_ptr(stop_panel_ptr) {
    // Build new encoder manager with 4 selections.
    _em = EncoderManager(encoder_ptr, 4);
  }

void EditPanel::start() {

  // Start the selection encoder.
  _em.start();

  // Clear display.
  _disp_ptr->clearDisplay();

  // Write first line.
  _disp_ptr->setCursor(1, 0);
  _disp_ptr->print(_top_text);

  // Write second line and add default tidal volume value.
  _disp_ptr->setCursor(1, 1);
  _disp_ptr->print(_tv_text + _vs_ptr->tidal_volume + _tv_units);

  // Write third line and add default respiration rate value.
  _disp_ptr->setCursor(1, 2);
  _disp_ptr->print(_rr_text + _vs_ptr->respiration_rate + _rr_units);
  
  // Write fourth line and add default i:e ratio.
  _disp_ptr->setCursor(1, 3);
  _disp_ptr->print(_i_e_text + _vs_ptr->inhale + ':' + _vs_ptr->exhale);
}

Panel* EditPanel::update() {
   _em.poll();

  // Check if we have a non-zero stop panel pointer and return if button pushed.
  if (_stop_panel_ptr != 0 && _stop_button_ptr->getButtonState()) {
    return _stop_panel_ptr; 
  }

  // If we are not in edit mode and the button pushed, edit current selection.
  if (!_edit && _em_button_ptr->getButtonState()) {

    // Selected confirm settings, exit and run device.
    if (_row == 0) {
      return _run_panel_ptr;
    }

    // Enable edit mode.
    _edit = true;

    // Set cursor to flash.
    _disp_ptr->blinkingOn();

    // Set encoder manager to give selections based on selected quantity.
    int num_selections;
    int starting_selection;

    switch (_row) {
      // Set selections for tidal volume.
      case 1:
        num_selections = (_max_tidal_volume - _min_tidal_volume) / _delta_tidal_volume;
        starting_selection = (_vs_ptr->tidal_volume - _min_tidal_volume) / _delta_tidal_volume;
        break;
      // Set selections for respiration rate.
      case 2:
        num_selections = (_max_respiration_rate - _min_respiration_rate) / _delta_respiration_rate;
        starting_selection = (_vs_ptr->respiration_rate - _min_respiration_rate) / _delta_respiration_rate;
        break;
      // Set selections for i:e ratio.
      case 3:
        num_selections = (_max_exhale - _min_exhale) / _delta_exhale;
        starting_selection = (_vs_ptr->exhale - _min_exhale) / _delta_exhale;
        break;
    }

    // Update settings to encoder manager.
    _em.setNumOptions(num_selections);
    _em.setSelection(starting_selection);
    
  
  // If we are in edit mode and the button was not pushed, encoder movement changes value.
  } else if (_edit && !_em_button_ptr->getButtonState()) {

    switch (_row) {
      // Edit tidal volume.
      case 1:
        // Calculate new tidal volume amount.
        _vs_ptr->tidal_volume = _min_tidal_volume + _em.getSelection() * _delta_tidal_volume;

        // Write to the display.
        _disp_ptr->setCursor(1 + _tv_text_length, 1);
        _disp_ptr->print(_vs_ptr->tidal_volume);
        break;
        
      // Edit respiration rate to new value.
      case 2:
        // Calculate new respitory rate.
        _vs_ptr->respiration_rate = _min_respiration_rate + _em.getSelection() * _delta_respiration_rate;
        
        // Write to the display.
        _disp_ptr->setCursor(1 + _rr_text_length, 2);
        _disp_ptr->print(_vs_ptr->respiration_rate);
        break;

      // Edit i:e ratio.
      case 3:
        // Calculate new i:e ratio.
        _vs_ptr->exhale = _min_exhale + _em.getSelection() * _delta_exhale;

        // Write to the display.
        _disp_ptr->setCursor(1 + _i_e_text_length, 3);
        _disp_ptr->print(_vs_ptr->exhale);
        break;
    }

    //Set cursor back to row so blinking continues.
    _disp_ptr->setCursor(0,_row);

  // If we are in edit mode and the button was pushed, exit edit mode.
  } else if (_edit && !_em_button_ptr->getButtonState()) {
    
    // Disable edit mode.
    _edit = false;

    // Stop cursor blinking.
    _disp_ptr->blinkingOff();

    // Set encoder manager back to 4 selections and to the row.
    _em.setNumOptions(4);
    _em.setSelection(_row);

  // If we are not in edit mode and the button was not pushed, move cursoe.
  } else if (!_edit && !_em_button_ptr->getButtonState()) {
   
    // Check if we've moved the cursor.
    if (_em.getSelection() != _row) {
      // Remove old cursor on the display.
      _disp_ptr->setCursor(0, _row);
      _disp_ptr->remove();

      // Write the new cursor on the display.
      _disp_ptr->setCursor(0,_em.getSelection());
      _disp_ptr->print(">");

      // Set the old row to the current row.
      _row = _em.getSelection();
    }
  }
}

RunningPanel::RunningPanel(NhdDisplay* disp_ptr, Encoder* encoder_ptr, ButtonManager* em_button_ptr, ButtonManager* stop_button_ptr, VentSettings* vs_ptr, Panel* stop_panel_ptr) :
  Panel{disp_ptr, encoder_ptr, em_button_ptr, stop_button_ptr, vs_ptr},
  _stop_panel_ptr(stop_panel_ptr) {}

String RunningPanel::formatTime() {
  return _top_text + _vs_ptr->hours + ":" + _vs_ptr->minute + ":" + _vs_ptr->seconds;
}

void RunningPanel::start() {

  // Reset time.
  _vs_ptr->hours = 0;
  _vs_ptr->minute = 0;
  _vs_ptr->seconds = 0;

  // Change mode to load new settings.
  _vs_ptr->mode = 'L';

  // Clear display.
  _disp_ptr->clearDisplay();

  // Write first line.
  _disp_ptr->setCursor(0, 0);
  _disp_ptr->print(formatTime());

  // Write second line and add default tidal volume value.
  _disp_ptr->setCursor(0, 1);
  _disp_ptr->print(_tv_text + _vs_ptr->tidal_volume + _tv_units);

  // Write third line and add default respiration rate value.
  _disp_ptr->setCursor(0, 2);
  _disp_ptr->print(_rr_text + _vs_ptr->respiration_rate + _rr_units);
  
  // Write fourth line and add default i:e ratio.
  _disp_ptr->setCursor(0, 3);
  _disp_ptr->print(_i_e_text + _vs_ptr->inhale + ':' + _vs_ptr->exhale);
}

Panel* RunningPanel::update() {
  
  // Check if we have a non-zero stop panel pointer and return if button pushed.
  if (_stop_panel_ptr != 0 && _stop_button_ptr->getButtonState()) {
    return _stop_panel_ptr; 
  }

  // Update and display time if needed.


}



void PausePanel::start() {

}

Panel* PausePanel::update() {

}

