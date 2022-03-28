#include "Timing.h" 
#include <time.h> 

CTiming::CTiming() 
{
	ticksPerSecond.QuadPart = 0;
	tick.QuadPart = 0; // a point in time
	time.QuadPart = 0;// for converting tick into real time

	startFrame.QuadPart = 0;
	stopFrame.QuadPart = 0;
	currentTick.QuadPart = 0;
	nFrames.QuadPart = 0;
	Ticks_To_Wait.QuadPart = 0;
	tickspassed.QuadPart = 0;
	ticksleft.QuadPart = 0;
	prev_frame.QuadPart = 0;
	framedelay.QuadPart = 0;

	int done = 0;

	// Global variables for measuring fps
	lastUpdate        = 0;
	fpsUpdateInterval = 0.5f;
	numFrames         = 0;
	fps               = 0;
   // Set current and previous time to the clock time at initialisation. 
   // Otherwise mDelta = mCurrentTime - mPrevious in CalculateFrameRate() will 
   // give an absurd number during its first call and screw up all the physics 
   QueryPerformanceFrequency(&ticksPerSecond); 
}// cTiming

void CTiming::Init()
{
	QueryPerformanceCounter(&framedelay);
	QueryPerformanceFrequency(&ticksPerSecond);
	prev_frame.QuadPart = 0;
	ticksleft.QuadPart = 0;
}

void CTiming::StartTimer()
{
	QueryPerformanceCounter(&startFrame);
	//QueryPerformanceFrequency(&ticksPerSecond);
}

void CTiming::Wait(int MaxFrameRate)
{
	nFps = MaxFrameRate;
	Ticks_To_Wait.QuadPart = ticksPerSecond.QuadPart/MaxFrameRate;
}

void CTiming::FPSloop()
{
	done = 0;
	do
	{
		QueryPerformanceCounter(&time);
		tickspassed.QuadPart = time.QuadPart - prev_frame.QuadPart;
		ticksleft.QuadPart = Ticks_To_Wait.QuadPart - tickspassed.QuadPart;

		if(time.QuadPart < prev_frame.QuadPart)
			done = 1;
		if(tickspassed.QuadPart >= Ticks_To_Wait.QuadPart)
			done = 1;
	}
	while(!done);

	prev_frame = time;
}

int CTiming::GetTicksToWait()
{
	return (int)((__int64)Ticks_To_Wait.QuadPart);
}

// Called once for every frame
float CTiming::UpdateFPS()
{
  numFrames++;
  float currentUpdate = time.QuadPart;
  if( currentUpdate - lastUpdate > fpsUpdateInterval )
  {
    fps = numFrames / (currentUpdate - lastUpdate);
    lastUpdate = currentUpdate;
    numFrames = 0;
	return fps;
  }
  
}

float CTiming::SetSpeedFactor()
{
  QueryPerformanceCounter(&currentTick);
  //This frame's length out of desired length
  speedfactor = (float)(currentTick.QuadPart-framedelay.QuadPart)/((float)ticksPerSecond.QuadPart/nFps);
  fps = nFps/speedfactor;
  if (speedfactor <= 0)
    speedfactor = 1;

  framedelay = currentTick;
  return fps;
}
