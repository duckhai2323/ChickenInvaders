#include"CommonFunction.h"
#include"BaseObject.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
baseobject background;

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0)
	{
		return 0;
	}
	else
	{
		window = SDL_CreateWindow("Chicken Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			return 0;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				return 0;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) 
				{
					return 0;
				}
			}
		}
	}
	return 1;
}

void close()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = NULL;
	renderer = NULL;
	IMG_Quit();
	SDL_Quit();
}

int  main(int arv,char* argv[])
{
	int run = -(SCREEN_WIDTH*5);
	bool is_run = true;

	if (!init())
	{
		return 0;
	}
	else
	{
		if (!background.LoadImage("background6.png", renderer))
		{
			return 0;
		}
		else
		{
			background.SetRect(0,run);
			bool quit = false;
			SDL_Event e;
			while (!quit)
			{
				while (SDL_PollEvent(&e))
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}

				SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
				SDL_RenderClear(renderer);

				if (is_run)
				{
					run += 40;
					background.SetRect(0, run);
					background.Render(renderer);
					if (run >= 0)
					{
						is_run = false;
					}
				}
					else
					{
						background.Render(renderer);
					}
				SDL_RenderPresent(renderer);
			}
		}
	}
		close();
		return 0;
}