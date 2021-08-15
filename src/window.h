#pragma once

#include <iostream>
#include <SDL.h>
#include "maths.h"
#include "fractal.cuh"
#include "timer.h"
#include "settings.h"


enum class mouseSettings { MOVE, MORPH };


struct variable
{
	PERSISION x, y;
};


class Window
{
	PERSISION x, y, zoom;
	PERSISION mousePos[2], prevmousePos[2];
	mouseSettings mouseSetting;
	int wasd[6], settingKeyState[3];

	int w, h;
	bool IsOpen;

	SDL_Window* window;
	SDL_Renderer* renderer;
	Fractal* fractal;

	variable variable;
	bool holdingVariable;

public:
	bool mandel;

	Window(int w, int h, const char* title, Fractal* fractal);
	~Window();

	inline SV2D getSize() { return SV2D((float)w, (float)h); }
	void pollEvent(PERSISION deltaTime);
	void render();
	SV2D worldToScreen(PERSISION _x, PERSISION _y);
	SV2D screenToWorld(PERSISION _x, PERSISION _y);
	inline bool IsRunning() { return IsOpen; }
};