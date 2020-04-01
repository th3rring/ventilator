#ifndef encodermanager_h
#define encodermanager_h

#include "Arduino.h"
#include "Encoder.h"

class EncoderManager {

  public:
    EncoderManager(Encoder* encoder_ptr, int num_options);

    void start();
    void poll();
    int getSelection();
    void close();

  private:

    const byte COUNTS_PER_STEP = 4;

    Encoder* _encoder_ptr;
    long* _pos_ptr;
    int _selection;
    int _num_options;

};

#endif
