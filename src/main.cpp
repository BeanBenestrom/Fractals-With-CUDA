#include <thread>
#include "settings.h"
#include "window.h"


int main(int argc, char* argv[])
{
	char decision;

	std::cout << "0 - Julia Set\n";
	std::cout << "1 - MandelBrot Set\n";
	std::cin >> decision;

	if (decision != '0' && decision != '1') { return 0; }

	Fractal fractal(DEFAULT_SCREEN_SIZE_X, DEFAULT_SCREEN_SIZE_Y);
	Window window(DEFAULT_SCREEN_SIZE_X, DEFAULT_SCREEN_SIZE_Y, "Factal Program", &fractal); 

	window.mandel = (int)(decision - '0');

	int fpsMilliseconds = 1000 / FPS;
	int frameTime;
	double previousFrameTime = (PERSISION)(1/FPS);
	
	// std::thread _thread(window.pollEvent, FPS);

	while (window.IsRunning())
	{
		{
			Timer timer;
			frameTime = SDL_GetTicks();

			window.pollEvent(previousFrameTime);
			window.render();

			// Set framerate
			frameTime = SDL_GetTicks() - frameTime;
			if (frameTime < fpsMilliseconds) { SDL_Delay(fpsMilliseconds - frameTime); }

			previousFrameTime = (PERSISION)frameTime * 0.001;
			// std::cout << (int)(1 / ((float)frameTime * 0.001f)) << "\n";
		}
		std::cout << '\n';
	}
	
	return 0;
}
