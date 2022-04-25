#include"CommonFunction.h"
#include"BaseObject.h"
#include"SpaceObject.h"
#include"BulletObject.h"
#include"GiftObject.h"
#include"TextObject.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
baseobject background;
spaceobject space;
TTF_Font* font = NULL;
textobject textTime;

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

				if (TTF_Init() == -1)
				{
					return false;
				}
			}
		}
	}
	return 1;
}

bool check_collision(const SDL_Rect& object1, const SDL_Rect& object2) {
	int left_a = object1.x;
	int right_a = object1.x + object1.w;
	int top_a = object1.y;
	int bottom_a = object1.y + object1.h;

	int left_b = object2.x;
	int right_b = object2.x + object2.w;
	int top_b = object2.y;
	int bottom_b = object2.y + object2.h;

	if (left_a > right_b || right_a < left_b || top_a > bottom_b || bottom_a < top_b) {
		return false;
	}
	return true;
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
	int bullet_level = 0;
	textTime.SetTextColor(textobject::WHILE_TYPE);
	if (!init())
	{
		return 0;
	}
	else
	{
		font = TTF_OpenFont("font1.ttf", 30);
		if (font == NULL)
		{
			std::cout << "Failed to load Font";
			return 0;
		}
		if (!background.LoadImage("background6.png", renderer))
		{
			return 0;
		}
		if (!space.LoadImage("rocket.png", renderer))
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
					else space.InputAction(e,renderer,bullet_level);
				}

				SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
				SDL_RenderClear(renderer);

				if (is_run)
				{
					run += 3;
					background.SetRect(0, run);
					background.Render(renderer);
					if (run+3 >= 0)
					{
						is_run = false;
					}
				}
					else
					{
						background.Render(renderer);
					}

				space.Move();
				space.Show(renderer);
                space.HandleBullet(renderer);

				std::string text_time = "Time : ";
				Uint32 time = SDL_GetTicks() / 1000;
				std::string time_ = std::to_string(time);
				text_time += time_;
				textTime.SetText(text_time);
				textTime.SetRect(1000, 10);
				textTime.ShowText(font, renderer);
				SDL_RenderPresent(renderer);
			}
		}
	}
		close();
		return 0;
}