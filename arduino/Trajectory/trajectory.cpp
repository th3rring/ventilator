#include "Arduino.h"
#include "trajectory.h"

Trajectory::Trajectory (uint8_t traj_pos[], uint8_t traj_times[]):
  // Double check that this assignment works as expected
  _traj_pos(traj_pos),
  _traj_times(traj_times),
  _cur_step(0),
  _direction(true)
  {
    // Initialize the length to be that of the position array.
    _length = sizeof(_traj_pos);

    // Calculate the total time
    _tot_time = 0;

    for (int i = 0; i < _length; i++) {
      _tot_time += *(_traj_times + i);
    }
  }

void Trajectory::nextStep(uint8_t* pos, uint8_t* dur) {

  // Code to throw exceptions if we reach end
  //if (_cur_step == 0 && _direction == false) {
    //throw "Cannot go backwards from start of trajectory.";
  //} else if(_cur_step >= _length - 1 && _direction == true){
    //throw "Cannot go forward past end of trajectory.";
  //}
  
  // Switch the direction of the trajectory if we're at the end.
  if (_cur_step == 0 && _direction == false) {
    _direction = true;
  } else if(_cur_step >= _length - 1 && _direction == true){
    _direction = false;
  }

  // Find current position and duration
  *pos =  *(_traj_pos + _cur_step);
  *dur =  *(_traj_times + _cur_step);

  // Move the counter forward to the next step
  if (_direction) {
    _cur_step++;
  } else {
    _cur_step--; 
  }
}

void Trajectory::setDirection(bool direction) {
  _direction = direction;
}

void Trajectory::reset(uint8_t traj_pos[], uint8_t traj_times[]) {
  _traj_pos = traj_pos;
  _traj_times = traj_times;

  _length = sizeof(_traj_pos);
  _direction = true;
  _tot_time = 0;

  for (int i = 0; i < _length; i++) {
    _tot_time += *(_traj_times + i);
  }
}

int Trajectory::getTrajTime() {
  return _tot_time;
}

int Trajectory::getLength() {
  return _length;
}

int Trajectory::getCurrentStep() {
  return _cur_step;
}
