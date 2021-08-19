
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string>
#include <ctype.h>
#include <SDL.h>
#undef main
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_types.h>
#include <SDL_keycode.h>

using namespace std;

SDL_Surface* gHelloWorld = NULL;
SDL_Window* window = NULL;
SDL_Surface* surface = NULL;
int WINDOW_HEIGHT = 600;
int WINDOWS_WIDTH = 800;
typedef void (*importFunction)();

int destroyWindows();
void SDL_CLOSE();

int main()
{
	bool quit = false;

	window = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOWS_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

	surface = SDL_GetWindowSurface(window);

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) == -1)
	{
		cerr << "Error initializing SDL!" << SDL_GetError() << endl;
		return 1;
	}
	else
	{

		SDL_Event e;
		SDL_Rect player = { 300, 550, 230, 32 };
		Uint32 player_color = SDL_MapRGB(surface->format, 255, 50, 100);

		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				auto keyDown = e.key.keysym.sym;

				switch (e.type)
				{
				case SDL_QUIT:quit = true;break;
				case SDL_KEYDOWN:
					switch (keyDown)
					{
					case SDLK_RIGHT:
						if ((player.x + 32) < 560)
							player.x += 32;
					destroyWindows();

					
						break;
					case SDLK_LEFT:
						if ((player.x - 32) >= 10)
							player.x -= 32;
						break;
					/*case SDLK_UP:
						if ((player.y - 32) >= 0)
							player.y -= 32;
						break;
					case SDLK_DOWN:
						if ((player.y + 32) < WINDOW_HEIGHT)
							player.y += 32;
						break;*/
					}
				default:
					break;
				}


				SDL_BlitSurface(NULL, NULL, surface, NULL);

				SDL_Rect retangulo;

				retangulo.w = WINDOWS_WIDTH * 3 / 4;
				retangulo.h = WINDOW_HEIGHT * 3 / 4;
				retangulo.x = (WINDOWS_WIDTH - retangulo.w) / 2;
				retangulo.y = (WINDOW_HEIGHT - retangulo.h) / 2;
				SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 20, 60, 130));
				SDL_FillRect(surface, &retangulo, SDL_MapRGB(surface->format, 120, 80, 150));

				SDL_Rect retangulo_green;
				retangulo_green.w = WINDOWS_WIDTH / 2;
				retangulo_green.h = WINDOW_HEIGHT / 2;
				retangulo_green.x = (WINDOWS_WIDTH - retangulo_green.w) / 2;
				retangulo_green.y = (WINDOW_HEIGHT - retangulo_green.h) / 2;
				SDL_FillRect(surface, &retangulo_green, SDL_MapRGB(surface->format, 200, 255, 20));

				SDL_FillRect(surface, &player, player_color);
				SDL_UpdateWindowSurface(window);
			}
		}

		SDL_CLOSE();

		return 0;
	}
}

void SDL_CLOSE()
{
	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}
int destroyWindows()
{
	importFunction EndWindows;

	HINSTANCE hinstLib = LoadLibrary((LPCWSTR)L"Win32Power.dll");

	if (hinstLib == NULL) {
		cerr << "ERRO: não foi possível carregar a DLL\n" << endl;
		return 1;
	}

	EndWindows = (importFunction)GetProcAddress(hinstLib, "EndWindows");

	if (EndWindows == NULL) {
		cerr << "ERRO: não foi possível achar a função na DLL\n" << endl;
		FreeLibrary(hinstLib);
		return 1;
	}

	// Chama função.
	EndWindows();

	// Descarrega arquivo DLL
	FreeLibrary(hinstLib);

	return 0;
}
