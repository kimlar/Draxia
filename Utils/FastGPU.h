#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// Need the max(a,b) macro undefined because it is interfering with this file
#undef max

extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001; // BUG! Setting it to 0 does not disable Optimus
	_declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

/*
void EnableHighPerformanceGPU(int enable)
{
	AmdPowerXpressRequestHighPerformance = NvOptimusEnablement = (enable ? 1 : 0);
}
*/
