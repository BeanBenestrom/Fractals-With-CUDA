//#include "eventManager.h"
//
//
//void EventManager::pollEvent()
//{
//	SDL_Event event;
//
//	while (SDL_PollEvent(&event))
//	{
//		switch (event.type)
//		{
//		case SDL_QUIT: IsOpen = false;
//			break;
//		case SDL_KEYDOWN:
//			switch (event.key.keysym.sym)
//			{
//			case SDLK_w: wasd[0] = 1;
//				break;
//			case SDLK_a: wasd[1] = 1;
//				break;
//			case SDLK_s: wasd[2] = 1;
//				break;
//			case SDLK_d: wasd[3] = 1;
//				break;
//			case SDLK_q: wasd[4] = 1;
//				break;
//			case SDLK_e: wasd[5] = 1;
//				break;
//			case SDLK_1: mouseSetting = mouseSettings::MOVE;
//				break;
//			case SDLK_2: mouseSetting = mouseSettings::MORPH;
//			}
//			break;
//		case SDL_KEYUP:
//			switch (event.key.keysym.sym)
//			{
//			case SDLK_w: wasd[0] = 0;
//				break;
//			case SDLK_a: wasd[1] = 0;
//				break;
//			case SDLK_s: wasd[2] = 0;
//				break;
//			case SDLK_d: wasd[3] = 0;
//				break;
//			case SDLK_q: wasd[4] = 0;
//				break;
//			case SDLK_e: wasd[5] = 0;
//				break;
//			}
//			break;
//		case SDL_WINDOWEVENT:
//			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
//			{
//				SDL_GetWindowSize(window, &w, &h);
//				fractal->changeArea(w, h);
//			}
//			break;
//		case SDL_MOUSEBUTTONDOWN:
//			switch (event.button.button)
//			{
//			case SDL_BUTTON_LEFT:
//				switch (mouseSetting)
//				{
//				case mouseSettings::MOVE:
//					break;
//				case mouseSettings::MORPH:
//					break;
//				}
//			case SDL_BUTTON_RIGHT: std::cout << "noob\n"; settingKeyState[1] = 1;
//				break;
//			}
//		case SDL_MOUSEBUTTONUP:
//			switch (event.button.button)
//			{
//			case SDL_BUTTON_RIGHT: settingKeyState[1] = 0;
//				break;
//			}
//			break;
//		}
//	}
//}