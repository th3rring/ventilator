#include "Arduino.h"
#include "trajectory.h"

Trajectory::Trajectory(int delta_t, int* positions, int length):
  _delta_t(delta_t),
  _cur_step(0),
  _length(length){

    //Serial.println(length);

    //Make a new array of length.
    //_traj_pos = new int[length];

    // Copy values from positions array to internal array.
    //for (int i = 0; i < length; i++){
      //*(_traj_pos + i) = *(positions + i);
    //}
    _traj_pos = positions;
  }

int Trajectory::nextStep() {

  // Switch the direction of the trajectory if we're at the end.
  if(_cur_step >= _length - 1 ) {
    _cur_step = 0;
  }

  // Find current position and duration
  int next =  *(_traj_pos + _cur_step);

  // Move the counter forward to the next step
  _cur_step++;

  return next;
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
