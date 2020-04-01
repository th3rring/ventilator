#ifndef ventsettings_h
#define ventsettings_h

typedef struct  {

  char mode;

  int respiration_rate;
  int inhale;
  int exhale;
  int tidal_volume;
  float hold_time;

  int hours;
  int minute;
  int seconds;
} VentSettings;
#endif
