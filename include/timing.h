#ifndef _TIMING_H_ 
#define _TIMING_H_ 

//! The timing class 
class CTiming 
{ 
public:

	LARGE_INTEGER ticksPerSecond; //frequency
	LARGE_INTEGER tick; // a point in time
	LARGE_INTEGER time;// for converting tick into real time

	LARGE_INTEGER startFrame;
	LARGE_INTEGER stopFrame;
	LARGE_INTEGER currentTick;
	LARGE_INTEGER nFrames;
	LARGE_INTEGER Ticks_To_Wait;
	LARGE_INTEGER tickspassed;
	LARGE_INTEGER ticksleft;
	LARGE_INTEGER prev_frame;
	LARGE_INTEGER framedelay;

	float         speedfactor;

	int done;
	int nFps;

	// Global variables for measuring fps
	float lastUpdate;
	float fpsUpdateInterval;
	unsigned int  numFrames;
	float fps;

   CTiming();		// Constructor 
   void Init();
   void StartTimer();
   void Wait(int MaxFrameRate);
   float UpdateFPS();
   void FPSloop();
	int GetTicksToWait();

	float SetSpeedFactor();
}; 
#endif
