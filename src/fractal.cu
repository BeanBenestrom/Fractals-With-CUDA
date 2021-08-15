// #include <complex>
#include "fractal.cuh"
#include <iostream>


__global__ void kernel(int w, int h, PERSISION x, PERSISION y, PERSISION zoom, PERSISION var_x, PERSISION var_y, bool mandel, int* d_outPut)
{
	int id = blockIdx.x * blockDim.x + threadIdx.x;

	if (id < w*h) 
	{  
		PERSISION _x = (id % w - (PERSISION)w / 2.0) * zoom + x;
		PERSISION _y = -(id / w - (PERSISION)h / 2.0) * zoom + y;
		PERSISION tempX = 0;
		int iterations = ITERATIONS;

		x = var_x;
		y = var_y;

		// if (_x == _y) { iterations = 0; }

		while (iterations > 0)
		{
			// if ((id % w - (double)w / 2.0) + 30 < (double)w) { iterations = 0; break; }

			/*tempX = (x * x * x - x * y * y) / (1 + x * x - y) + _x;
			y = (3 * x * x * y - y * y) / (1 + x * x - y) + _y;
			x = tempX;*/

			if (mandel)
			{
				tempX = _x + x * x - y * y;
				y = _y + 2 * x * y;
				x = tempX;

				if (x * x + y * y > 4.0) { break; }
			}
			else
			{
				tempX = _x * _x - _y * _y - var_x;
				_y = 2.0f * _x * _y - var_y;
				_x = tempX;

				if (_x * _x + _y * _y > 4.0) { break; }
			}

			/*tempX = _x + x * x - y * y;
			y = _y + 2 * abs(x * y);
			x = tempX;*/

			/*tempX = _x * _x - _y * _y - var_x;
			_y = 2.0f * _x * _y - var_y; 
			_x = tempX;*/

			
			iterations--;
		}

		d_outPut[id] = (int)(iterations / (float)ITERATIONS * 255);
	}
}


Fractal::Fractal(int w, int h)
{
	this->w = w; this->h = h;
	blockSize = BLOCK_SIZE;
	blockAmount = (int)ceil((float)w * (float)h / (float)BLOCK_SIZE);

	taskRunning = false;
	d_outPut = nullptr;

	h_outPut = new int[w * h];
	cudaMalloc((void**)&d_outPut, sizeof(int) * w * h);
}


Fractal::~Fractal()
{
	FreeMemory();
}


void Fractal::changeArea(int _w, int _h)
{
	FreeMemory();
	w = _w; h = _h;
	h_outPut = new int[w * h];
	cudaMalloc((void**)&d_outPut, sizeof(int) * w * h);
	cudaDeviceSynchronize();

	blockAmount = (int)ceil((float)w * (float)h / (float)BLOCK_SIZE);
}


void Fractal::FreeMemory()
{
	if (d_outPut != nullptr && h_outPut != nullptr)
	{
		cudaDeviceSynchronize();
		cudaFree(d_outPut);
		delete[] h_outPut;
		d_outPut = nullptr;
		h_outPut = nullptr;
		cudaDeviceSynchronize();
	}
}


void Fractal::calculate(PERSISION x, PERSISION y, PERSISION zoom, PERSISION var_x, PERSISION var_y, bool mandel)
{
	kernel <<< blockAmount, blockSize >>> (w, h, x, y, zoom, var_x, var_y, mandel, d_outPut);
	cudaDeviceSynchronize();

	cudaMemcpy(h_outPut, d_outPut, sizeof(int) * w * h, cudaMemcpyDeviceToHost);
	cudaDeviceSynchronize();
}