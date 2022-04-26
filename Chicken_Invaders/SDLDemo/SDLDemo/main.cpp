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

// Menu
baseobject menu0;
baseobject menu1;
TTF_Font* font_menu = NULL;
 int menu_num = 0;
const int num_item = 4;
SDL_Rect poss_item[num_item];
textobject text_item[num_item];

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

bool check_mouse_item(const int& x, const int& y, const SDL_Rect& rect)
{
	if (rect.x <= x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
	{
		return true;
	}
	return false;
}

void menu()
{
	if (!menu0.LoadImage("menu0.png", renderer))
	{
		return;
	}
	if (!menu1.LoadImage("menu1.png", renderer))
	{
		return;
	}


	text_item[0].SetText("Start");
	text_item[0].SetTextColor(textobject::BLACK_TYPE);
	text_item[0].ShowText(font_menu, renderer);
	poss_item[0].x = WINDOW_WIDTH / 2 - text_item[0].GetRect().w / 2;
	poss_item[0].y = WINDOW_HEIGHT - 250;
	text_item[0].SetRect(poss_item[0].x, poss_item[0].y);

	text_item[1].SetText("Information");
	text_item[1].SetTextColor(textobject::BLACK_TYPE);
	text_item[1].ShowText(font_menu, renderer);
	poss_item[1].x = WINDOW_WIDTH / 2 - text_item[1].GetRect().w / 2;
	poss_item[1].y = WINDOW_HEIGHT - 170;
	text_item[1].SetRect(poss_item[1].x, poss_item[1].y);

	text_item[2].SetText("Exit !");
	text_item[2].SetTextColor(textobject::BLACK_TYPE);
	text_item[2].ShowText(font_menu, renderer);
	poss_item[2].x = WINDOW_WIDTH / 2 - text_item[2].GetRect().w / 2;
	poss_item[2].y = WINDOW_HEIGHT - 90;
	text_item[2].SetRect(poss_item[2].x, poss_item[2].y);

	text_item[3].SetText("Back !");
	text_item[3].SetTextColor(textobject::BLACK_TYPE);
	text_item[3].ShowText(font_menu, renderer);
	poss_item[3].x = 10;
	poss_item[3].y = 10;
	text_item[3].SetRect(poss_item[3].x, poss_item[3].y);


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
		font_menu = TTF_OpenFont("font1.ttf", 45);
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
			//Handle_Menu
			menu();
			int xm = 0;
			int ym = 0;
			//SDL_GetMouseState(&xm, &ym);
			bool menu_Run = true;
			SDL_Event e_menu;
			while (menu_Run)
			{
				if (menu_num == 0)
				{
					text_item[0].ShowText(font_menu, renderer);
					text_item[1].ShowText(font_menu, renderer);
					text_item[2].ShowText(font_menu, renderer);
					menu0.Render(renderer);
					text_item[0].Render(renderer);
					text_item[1].Render(renderer);
					text_item[2].Render(renderer);
				}
				else if (menu_num == 1)
				{
					menu1.Render(renderer);
					text_item[3].ShowText(font_menu, renderer);
					text_item[3].Render(renderer);
				}
				while (SDL_PollEvent(&e_menu)!=0)
				{
					if (e_menu.type == SDL_QUIT)
					{
						menu_Run == false;
						return 0;
					}
					else if (e_menu.type == SDL_MOUSEMOTION)
					{
						SDL_GetMouseState(&xm, &ym);
						for (int t = 0; t < num_item; t++)
						{
							if (check_mouse_item(xm, ym, text_item[t].GetRect()))
							{
								text_item[t].SetTextColor(textobject::WHILE_TYPE);
							}
							else text_item[t].SetTextColor(textobject::BLACK_TYPE);
						}
					}
					else if (e_menu.type == SDL_MOUSEBUTTONDOWN)
					{
						xm = e_menu.button.x;
						ym = e_menu.button.y;
						for (int i = 0; i < num_item; i++)
						{
							if (check_mouse_item(xm, ym, text_item[i].GetRect()))
							{
								if (i == 0)
								{
									menu_Run = false;
								}
								else if (i == 1)
								{
									menu_num = 1;
       							}
								else if (i == 2)
								{
									return 0;
								}
								else if (i == 3)
								{
									menu_num = 0;
								}
							}
						}
					}
				}
				SDL_RenderPresent(renderer);
			}

			//Handle_Game
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
				textTime.Render(renderer);
				SDL_RenderPresent(renderer);
			}
		}
	}
		close();
		return 0;
}