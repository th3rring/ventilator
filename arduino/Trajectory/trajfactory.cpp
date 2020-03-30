#include "Arduino.h"
#include "trajfactory.h"

TrajFactory::TrajFactory(uint8_t respitory_rate, float i_e_ratio, float hold_time, uint8_t delta_t):
  _respitory_rate(respitory_rate),
  _i_e_ratio(i_e_ratio),
  _t_hold(hold_time),
  _delta_t(delta_t){}

Trajectory TrajFactory::build(uint8_t respitory_rate, float i_e_ratio, uint16_t setpoint, float hold_time, uint8_t delta_t){

  // Update internal parameters.
  _respitory_rate = respitory_rate;
  _i_e_ratio = i_e_ratio;
  _x_s = setpoint;
  _t_hold = hold_time;
  _delta_t = delta_t;

  // Calculate total cycle time based on respitory rate.
  _t_tot = 60.0/_respitory_rate;

  // Calculate breath cycle times.
  _t_out = (_t_tot - _t_hold) / (_i_e_ratio + 1);
  _t_in = _i_e_ratio * _t_out;

  // Take the hold time out of the exhale cycle. Do this to ensure respitory rate is correct.
  _t_out -= _t_hold;

  // Calculate kinematics for curve generation.
  float x_h = (_x_s + _x_0)/2.0;
  float v_in = 2*((_x_s - _x_0)/_t_in);
  float a_in = (v_in * v_in)/(_x_s-_x_0);
  float v_out = 2*((_x_s - _x_0)/_t_out);
  float a_out = (v_out * v_out)/(_x_s-_x_0);

  // Calculate the length of the new trajectory.
  _length = uint16_t (_t_tot * (1000 / _delta_t));

  // Make a new variable to hold the trajectory.
  uint16_t x[_length];

  // Calculate the timing of keypoints in the trajectory.
  uint16_t in_concave = uint16_t (1000*(_t_in/2.0));
  uint16_t in_convex = uint16_t (1000*_t_in);
  uint16_t hold_end = uint16_t (1000*(_t_in + _t_hold));
  uint16_t out_convex  = uint16_t (1000*(_t_in + _t_hold + _t_out/2.0));

  // Generate trajectory.
  for (uint16_t i = 0; i < _length; i++) {
    // Find trajectory time in ms.
    uint16_t t = _delta_t * i;
    
    // Calculate in stroke concave portion.
    if (t < in_concave) {
      x[i] = _x_0 + a_in*(t/1000.0)*(t/1000.0) / 2;

    // Calculate in stroke convex portion.
    } else if (t >= in_concave && t < in_convex) {
      float cur_t = (t - in_concave)/1000.0;
      x[i] = x_h + v_in*cur_t - a_in*cur_t*cur_t/2;

    // Calculate hold position.
    } else if (t >= in_convex && t < hold_end) {
        x[i] = _x_s;

    // Calculate out stroke convex portion.
    } else if (t >= hold_end && t < out_convex) {
    
    
    } else {
    
    }

  
  
  }
  
  // If there's a trajectory saved, delete it.
  if (_traj_pos != 0) {
    delete [] _traj_pos; 
  }

  // Create new array for trajectory.
  //_traj_pos = new uint16_t[_length];


}

