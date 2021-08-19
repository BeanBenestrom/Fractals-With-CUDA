#include <new>
#include "window.h"


Window::Window(int w, int h, const char* title, Fractal* fractal) : w(w), h(h), x(STARTING_X), y(STARTING_Y), fractal(fractal)
{
	IsOpen = false;

	if (SDL_Init(SDL_INIT_VIDEO) == -1) { std::cerr << "[!] Window: SDL failed to initialize!\n"; return; }

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_RESIZABLE);
	if (!window) { std::cerr << "[!] Window: Window couldn't be created!\n"; return; }

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) { std::cerr << "[!] Window: Renderer couldn't be created!\n"; return; }

	zoom = (STARTING_ZOOM == 0 ? 10 / (PERSISION)w : STARTING_ZOOM);

	variable.x = VARIABLE_STARTING_X;
	variable.y = VARIABLE_STARTING_Y;

	// holdingVariable = false;

	IsOpen = true;
};


Window::~Window()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
};


void Window::pollEvent(PERSISION deltaTime)
{
	prevmousePos[0] = mousePos[0]; prevmousePos[1] = mousePos[1];

	SDL_Event event;

	// Get mouse position
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	mousePos[0] = mouseX; mousePos[1] = mouseY;

	SV2D _mousePos = screenToWorld(mouseX, mouseY);
	

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: IsOpen = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE: IsOpen = false;
				break;
			case SDLK_w: wasd[0] = 1;
				break;
			case SDLK_a: wasd[1] = 1;
				break;
			case SDLK_s: wasd[2] = 1;
				break;
			case SDLK_d: wasd[3] = 1;
				break;
			case SDLK_q: wasd[4] = 1;
				break;
			case SDLK_e: wasd[5] = 1;
				break;
			case SDLK_r: x = 0; y = 0; zoom = 10/(PERSISION)w;
				break;
			case SDLK_1: mouseSetting = mouseSettings::MOVE;
				break;
			case SDLK_2: mouseSetting = mouseSettings::MORPH;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_w: wasd[0] = 0;
				break;
			case SDLK_a: wasd[1] = 0;
				break;
			case SDLK_s: wasd[2] = 0;
				break;
			case SDLK_d: wasd[3] = 0;
				break;
			case SDLK_q: wasd[4] = 0;
				break;
			case SDLK_e: wasd[5] = 0;
				break;
			}
			break;
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				SDL_GetWindowSize(window, &w, &h);
				fractal->changeArea(w, h);
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT: 
				switch (mouseSetting)
				{
				case mouseSettings::MOVE: x = _mousePos.x; y = _mousePos.y;
					break;
				case mouseSettings::MORPH: settingKeyState[0] = 1;
					break;
				}
				break;
			case SDL_BUTTON_RIGHT: settingKeyState[1] = 1;
				break;
			case SDL_BUTTON_MIDDLE: 
				std::cout << "Cam POSITION: " << x << " " << y << " " << zoom << "\n";	
				std::cout << "VARIABLE POSITION: " << variable.x << " " << variable.y << "\n";
				std::cout << "Mouse POSITION: " << _mousePos.x << " " << _mousePos.y << " " << zoom << "\n";
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT: settingKeyState[0] = 0; holdingVariable = false;
			case SDL_BUTTON_RIGHT: settingKeyState[1] = 0;
				break;
			}
			break;
		case SDL_MOUSEMOTION:
			if (settingKeyState[0] && mouseSetting == mouseSettings::MORPH)
			{
				SV2D dot = worldToScreen(variable.x, variable.y);
				if ((dot.x - 5 < mouseX) && (mouseX < dot.x + 5))
				{
					if ((dot.y - 5 < mouseY) && (mouseY < dot.y + 5))
					{
						holdingVariable = true;
					}
				}
			}
			if (settingKeyState[1])
			{
				SV2D pos2 = screenToWorld(prevmousePos[0], prevmousePos[1]);
				x -= _mousePos.x - pos2.x;
				y -= _mousePos.y - pos2.y;
			}
			break;
		}		
	}

	if (wasd[0]) { y += 200.0 * zoom * deltaTime; }
	if (wasd[1]) { x -= 200.0 * zoom * deltaTime; }
	if (wasd[2]) { y -= 200.0 * zoom * deltaTime; }
	if (wasd[3]) { x += 200.0 * zoom * deltaTime; }
	if (wasd[4]) { zoom += 0.99 * zoom * deltaTime; }
	if (wasd[5]) { zoom -= 0.99 * zoom * deltaTime; }

	if (holdingVariable && settingKeyState[0]) { variable.x = _mousePos.x; variable.y = _mousePos.y; }
}


void Window::render()
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	SDL_RenderClear(renderer);

	{
		Timer timer;
		fractal->calculate(x, y, zoom, variable.x, variable.y, mandel);
	}
	{
		Timer timer;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				// int iteration = sin(fractal->getPixel(j, i) * 0.5 + 0.5) * 255;
				float value = (-cos(fractal->getPixel(j, i) * 0.05) * 0.5 + 0.5) * 255 / (float)255 * M_PI;
				//int iteration = fractal->getPixel(j, i);

				int r = abs(cos(value)) * 255;
				int g = sin(value) * 255;
				int b = abs(cos(value)) * 255;

				if (value < M_PI * 0.5) { b = 0; }
				else { r = 0; }

				if (value == 0) { b = 0; r = 0; g = 0; }


				//float value = (cos(fractal->getPixel(j, i) * 0.05) * 0.5 + 0.5) * 255;

				//int r = 255 - value;
				//int g = (255 - value) * 0.4; // 127.5
				//int b = 0;

				/*if (value == 0) { b = 0; r = 0; g = 0; }*/

				SDL_SetRenderDrawColor(renderer, r, g, b, 0);
				SDL_RenderDrawPoint(renderer, j, i);
			}
		}

		if (mouseSetting == mouseSettings::MORPH)
		{
			SV2D dot = worldToScreen(variable.x, variable.y);

			SDL_Rect rect;
			rect.w = 5;
			rect.h = 5;
			rect.x = (int)dot.x;
			rect.y = (int)dot.y;

			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
			SDL_RenderDrawRect(renderer, &rect);
		}

		SDL_RenderPresent(renderer);
	}
}


SV2D Window::worldToScreen(PERSISION _x, PERSISION _y)
{
	_x -= x;
	_y -= y;

	_x /= zoom;
	_y /= zoom;

	_y = -_y;

	_x += w / 2;
	_y += h / 2;

	return SV2D(_x, _y);
}


SV2D Window::screenToWorld(PERSISION _x, PERSISION _y)
{

	_x -= w/2;
	_y -= h/2;

	_y = -_y;

	_x *= zoom;
	_y *= zoom;

	_x += x;
	_y += y;

	return SV2D(_x, _y);
}