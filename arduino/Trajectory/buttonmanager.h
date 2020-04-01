#ifndef buttonmanager_h
#define buttonmanager_h

#include "Arduino.h"

class ButtonManager {

  public:
    ButtonManager(int pin, bool highDefault);

    void poll();
    bool getButtonState();

  private:
    // Button pin for this manager
    int _button_pin;
    // Sets whether the button is normally high or not.
    bool _high_default;
    bool _button_state;
    bool _last_state;

    unsigned long _last_debounce;
    unsigned long _debounce_delay;
};

#endif
