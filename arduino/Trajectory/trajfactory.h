#ifndef trajfactory_h
#define trajectory_h

#include "Arduino.h"
#include "trajectory.h"

// Single byte integer alias
using uint8_t = unsigned char;
using uint16_t = unsigned int;

class TrajFactory {
  public:
    // Init traj with parameters.
    TrajFactory(uint8_t respitory_rate, float i_e_ratio, float hold_time, uint8_t delta_t);

    // Init
    TrajFactory();

    // TrajFactory rebuild functions
    Trajectory build(uint8_t respitory_rate, float i_e_ratio, uint16_t setpoint, float hold_time);
    Trajectory buildSetpoint(uint16_t setpoint);
    
    // Getters
    int getTotalTime();
    int getInhaleTime();
    int getExhaleTime();
    int getDeltaTime();
    int getLength();

  private:
    uint16_t _length;
    // Set trajectory array pointer to 0 to know to delete.
    uint16_t* _traj_pos = 0;

    uint8_t _respitory_rate;
    float _i_e_ratio;

    uint16_t _x_s;
    uint16_t _x_0;

    float _t_in;
    float _t_out;
    float _t_hold;
    float _t_tot;
    uint8_t _delta_t;




    // True value is increasing
    bool _direction;

    int calcTotalTime();

};
#endif
