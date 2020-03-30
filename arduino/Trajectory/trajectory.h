#ifndef trajectory_h
#define trajectory_h

#include "Arduino.h"

// Single byte integer alias
using uint8_t = unsigned char;
using uint16_t = unsigned int;

class Trajectory {
  public:
    Trajectory(uint8_t delta_t, uint16_t* positions, uint16_t length);
    Trajectory(char serialized[]);

    // Methods
    uint16_t nextStep();

    // Setters
    void setDirection(bool direction);
    
    // Getters
    int getLength();
    int getCurrentStep();
    int getDeltaTime();

  private:
    int _cur_step;
    int _length;
    uint16_t* _traj_pos;
    uint8_t _delta_t;
    // True value is increasing
    bool _direction;

};
#endif
