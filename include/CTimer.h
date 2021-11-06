#ifndef TIMER_H
#define TIMER_H

class framerate
{
public:
  float         targetfps;
  float         fps;
  LARGE_INTEGER tickspersecond;
  LARGE_INTEGER currentticks;
  LARGE_INTEGER framedelay;

  float         speedfactor;

  void          Init(float tfps);
  void          SetSpeedFactor();
};

#endif
