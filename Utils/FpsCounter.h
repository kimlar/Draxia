#pragma once

//
// TODO: Build this as a class
//

#include "SDL.h"



// FPS
double dtFps = 0;
Uint32 frameCount = 0;
Uint32 frameLastCount = 0;

inline bool FpsUpdate(double dt)
{
	// FPS
	frameCount++;
	dtFps += dt;
	if (dtFps >= 1)
	{
		DEBUG_PRINT("Average FPS: " << frameCount << "\t\tAverage dt: " << dt << " sec" << "\tdtFps:" << dtFps);
		dtFps -= 1;
		frameLastCount = frameCount;
		frameCount = 0;
		return true;
	}
	return false;
}

inline Uint32 FpsGet()
{
	return frameLastCount;
}
