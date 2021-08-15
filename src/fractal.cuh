#pragma once

#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <math.h>
#include "settings.h"


class Fractal
{
	int w, h;
	int blockAmount, blockSize;
	int* h_outPut; int* d_outPut;
	bool taskRunning;

public:
	Fractal(int w, int h);
	~Fractal();
	void changeArea(int _w, int _h);
	void FreeMemory();
	void calculate(PERSISION x, PERSISION y, PERSISION zoom, PERSISION var_x, PERSISION var_y, bool mandel);
	inline int getPixel(int x, int y) { return h_outPut[y * w + x]; }
};