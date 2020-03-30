#include "Arduino.h"
#include "trajectory.h"

Trajectory::Trajectory(uint8_t delta_t, uint16_t* positions, uint16_t length):
  _delta_t(delta_t),
  _cur_step(0),
  _direction(true),
  _length(length),
  _traj_pos(positions){}

uint16_t Trajectory::nextStep() {

  // Switch the direction of the trajectory if we're at the end.
  if (_cur_step == 0 && _direction == false) {
    _direction = true;
  } else if(_cur_step >= _length - 1 && _direction == true){
    _direction = false;
  }

  // Find current position and duration
  uint16_t next =  *(_traj_pos + _cur_step);

  // Move the counter forward to the next step
  if (_direction) {
    _cur_step++;
  } else {
    _cur_step--; 
  }

  return next;
}

void Trajectory::setDirection(bool direction) {
  _direction = direction;
}

int Trajectory::getLength() {
  return _length;
}

int Trajectory::getCurrentStep() {
  return _cur_step;
}

int Trajectory::getDeltaTime() {
  return _delta_t;
}
