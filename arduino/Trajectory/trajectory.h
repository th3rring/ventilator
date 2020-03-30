#ifndef trajectory_h
#define trajectory_h

#include "Arduino.h"

// Single byte integer alias
using uint8_t = unsigned char;

class Trajectory {
  public:
    Trajectory(uint8_t traj_pos[], uint8_t traj_times[]);

    // Methods
    void nextStep(uint8_t* pos, uint8_t* dur);

    // Setters
    void setDirection(bool direction);
    void reset(uint8_t traj_pos[], uint8_t traj_times[]);
    
    // Getters
    int getTrajTime();
    int getLength();
    int getCurrentStep();

  private:
    int _cur_step;
    int _length;
    int _tot_time;
    uint8_t* _traj_pos;
    uint8_t* _traj_times;
    // True value is increasing
    bool _direction;

    int calcTotalTime();

};
#endif
