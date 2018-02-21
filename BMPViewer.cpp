#include "BMPViewer.hpp"

void BMPViewer::BMPViewer::ShowBitMap(SDL_Surface* image)
{
	if (image == NULL) throw std::exception();
	//prepare window
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window * window = SDL_CreateWindow("BMP Viewer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_W, WINDOW_H,0);

	SDL_Surface* surface = SDL_GetWindowSurface(window);

	SDL_Rect pos = { (WINDOW_W - image->w) / 2,(WINDOW_H - image->h) / 2,image->w,image->h };

	SDL_BlitSurface(image, NULL, surface, &pos);

	SDL_UpdateWindowSurface(window);

	bool shutdown = false;
	while (!shutdown)
	{
		SDL_Event SDLEvent;
		while (SDL_PollEvent(&SDLEvent))
		{
			if (SDLEvent.type == SDL_KEYDOWN && SDLEvent.key.keysym.sym == SDLK_ESCAPE || SDLEvent.type == SDL_QUIT)
			{
				shutdown = true;
				break;
			}
		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
}
