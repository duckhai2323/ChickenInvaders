#include"Common_Function.h"
#include"Base_Object.h"
#include"MainObject.h"
#include"Bullet_Object.h"
#include"Threat_Object.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
mainobject rocket;
baseobject background;
std::vector<bulletobject*> BULLET_LIST;
threatobject* threatStone = new threatobject[NUM_THREAT];
SDL_Rect* threatAnimation = new SDL_Rect[NUM_ANIMATION];

bool init()
{
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return 0;
	}
	else
	{
		window = SDL_CreateWindow("Chicken Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			return 0;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				return 0;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					return 0;
				}

				////Set Rect_Animation
				threatAnimation[0].x = 0;
				threatAnimation[0].y = 0;
				threatAnimation[0].w = 111.8;
				threatAnimation[0].h = 90;

				threatAnimation[1].x = 111.8;
				threatAnimation[1].y = 0;
				threatAnimation[1].w = 111.8;
				threatAnimation[1].h = 90;

				threatAnimation[2].x = 223.6;
				threatAnimation[2].y = 0;
				threatAnimation[2].w = 111.8;
				threatAnimation[2].h = 90;

				threatAnimation[3].x = 334.4;
				threatAnimation[3].y = 0;
				threatAnimation[3].w = 111.8;
				threatAnimation[3].h = 90;

				threatAnimation[4].x = 447.2;
				threatAnimation[4].y = 0;
				threatAnimation[4].w = 111.8;
				threatAnimation[4].h = 90;

				threatAnimation[5].x = 599;
				threatAnimation[5].y = 0;
				threatAnimation[5].w = 111.8;
				threatAnimation[5].h = 90;

				threatAnimation[6].x =670.8 ;
				threatAnimation[6].y = 0;
				threatAnimation[6].w = 111.8;
				threatAnimation[6].h = 90;

				threatAnimation[7].x = 782.6;
				threatAnimation[7].y = 0;
				threatAnimation[7].w = 111.8;
				threatAnimation[7].h = 90;

				threatAnimation[8].x = 894.4;
				threatAnimation[8].y = 0;
				threatAnimation[8].w = 111.8;
				threatAnimation[8].h = 90;

				threatAnimation[9].x = 1006.2;
				threatAnimation[9].y = 0;
				threatAnimation[9].w = 111.8;
				threatAnimation[9].h = 90;

			}
		}
	}
	return 1;
	
}



void clean()
{
	background.close();
	rocket.close();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = NULL;
	renderer = NULL;
	IMG_Quit();
	SDL_Quit();
}
int main(int arv, char* argv[])
{
	bool is_Run = true;
	int run = -(SCREEN_BACKGROUND*5);
	srand((unsigned int)time(NULL));
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
			if (!rocket.LoadImage("rocket60.png", renderer))
			{
				return 0;
			}
			rocket.SetRect(500, 500);
			for (int i = 0; i < NUM_THREAT; i++)
			{
				if (!threatStone[i].LoadImage("chickenGreen.png", renderer))
				{
					return 0;
				}
				int temp = rand() % 1000;
				threatStone[i].SetRect(temp,-i*300);
				bulletobject* bullet_Threat = new bulletobject;
				threatStone[i].InitBullet(bullet_Threat, renderer);
			}
			
			bool quit = false;
			SDL_Event e;
			int temp = 0;
			while (!quit)
			{
				while (SDL_PollEvent(&e))
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else rocket.InputAction(e,renderer);
				}

				SDL_RenderClear(renderer);

				if (is_Run == true)
				{
					run += 2;
					background.SetRect(0, run);
					background.Render(renderer, NULL);
					if (run+2 >= 0)
					{
						is_Run = false;
					}
				}
				else
				{
					background.Render(renderer, NULL);
				}


				rocket.HandleMove();
				rocket.Render(renderer, NULL);

				BULLET_LIST = rocket.GetList();
				for (int i = 0; i < BULLET_LIST.size(); i++)
				{
					bulletobject* BULLET = BULLET_LIST.at(i);
					if (BULLET != NULL)
					{
						if (BULLET->GetMove() == true)
						{
							BULLET->HandleMove(0, 0);
							BULLET->Render(renderer, NULL);
						}
						else
						{
							if (BULLET != NULL)
							{
								  //BULLET_LIST[1]->close();
								  //rocket.SetBulletList(BULLET_LIST);
								 // BULLET->close();
							}
						}
					}
				}

				for (int i = 0; i < NUM_THREAT; i++)
				{
					threatStone[i].HandleMove(0, 0);
					threatStone[i].RenderClip(renderer, &threatAnimation[temp/5]);
					threatStone[i].MakeBullet(WINDOW_WIDTH, WINDOW_HEIGHT, renderer);

					bool is_coll1 = CheckCollistion(rocket.GetRect(), threatStone[i].GetRect());
					if (is_coll1 == true)
					{
						delete[] threatStone;
						clean();
						return 0;
					}

					std::vector<bulletobject*> b_list = rocket.GetList();
					for (int i = 0; i < b_list.size(); i++)
					{
						bulletobject* a = b_list.at(i);
						if (a != NULL)
						{
							bool is_coll2 = CheckCollistion(a->GetRect(), threatStone[i].GetRect());
							if (is_coll2 == true)
							{
								threatStone[i].Reset(-i * 300);
								rocket.RemoveBullet(i);
							}
						}
					}
				}
				temp++;
				if (temp / 5 >= NUM_ANIMATION)
				{
					temp = 0;
				}
				SDL_RenderPresent(renderer);
			}
		}
	}
	delete [] threatStone;
	clean();
	return 0;
}