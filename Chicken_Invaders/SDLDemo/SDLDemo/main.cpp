#include"CommonFunction.h"
#include"BaseObject.h"
#include"SpaceObject.h"
#include"BulletObject.h"
#include"GiftObject.h"
#include"TextObject.h"
#include"ThreatStone.h"
#include"Explosion.h"
#include"Chicken1.h"
#include"EggBreak.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
baseobject background;
spaceobject space;
explosion exp_;
eggbreak ebr_;
giftobject gift;
std::vector<threatstone*>stone_;
std::vector<chickenobject1*>chicken_;

//header
TTF_Font* font = NULL;
textobject textTime;
TTF_Font* font_Level = NULL;
textobject textLevel;
int Level = 1;
textobject text_stone_died;
int num_stone_died = 0;
int num_chicken_died = 0;
textobject text_skill;
textobject text_heart;
baseobject stone_small;
baseobject skill_heart;

// Menu
bool menu_Run = true;
SDL_Event e_menu;
baseobject menu0;
baseobject menu1;
TTF_Font* font_menu = NULL;
int menu_num = 0;
const int num_item = 4;
SDL_Rect poss_item[num_item];
textobject text_item[num_item];

//Return_Game_End_Game
TTF_Font* font_return = NULL;
textobject text_return;
TTF_Font* font_end = NULL;
textobject text_end;
int time_end_game = 0;

//Handle_Game
SDL_Event e;
bool quit = false;
int bullet_level = 0;
int run = -(SCREEN_WIDTH * 5);
bool is_run = true;

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
				font = TTF_OpenFont("font1.ttf", 25);
				font_menu = TTF_OpenFont("font1.ttf", 45);
				font_Level = TTF_OpenFont("font1.ttf", 30);
				font_return = TTF_OpenFont("font1.ttf", 50);
				font_end = TTF_OpenFont("font1.ttf", 60);
				if (font == NULL || font_menu == NULL || font_Level == NULL||font_return == NULL||font_end == NULL)
				{
					return 0;
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

void reset()
{
	Level = 1;
    run = -(SCREEN_WIDTH * 5);
	is_run = true;

	bullet_level = 0;
	space.set_bul_type(BLASTER);
	space.SetRect(WINDOW_WIDTH / 2 - SPACE_WIDTH / 2, WINDOW_HEIGHT / 2 - SPACE_HEIGHT / 2);
	space.SetHeart(MAIN_HEART);
	space.SetXY(0, 0);
	space.SetStatus(true);
	num_stone_died = 0;
	time_end_game = 0;

	for (int i = 0; i < NUM_STONE_THREAT; i++)
	{
		threatstone* stone = stone_.at(i);
		int Rand = rand() % 1000 + 10;
		stone->SetRect(Rand, -i * 200);
		stone->SetStatus(true);
	}

	for (int i = 0; i < NUM_CHIKEN1; i++)
	{
		chickenobject1* chicken_threat = chicken_.at(i);
		if (0 <= i && i <= 9)
		{
			chicken_threat->SetRect(-i * 100, 50);
		}
		else if (10 <= i && i <= 19)
		{
			chicken_threat->SetRect(-i * 100, 130);
		}
		else if (20 <= i && i <= 29)
		{
			chicken_threat->SetRect(-i * 100, 210);
		}
		if (30 <= i && i <= 39)
		{
			chicken_threat->SetRect(-i * 100, 290);
		}
		if (40 <= i && i <= 49)
		{
			chicken_threat->SetRect(-i * 100, 370);
		}
		chicken_threat->SetStatus(true);
	}
}

void menu(std::string item)
{
	if (!menu0.LoadImage("menu0_1.png", renderer))
	{
		menu_Run = false;
		quit = true;
	}
	if (!menu1.LoadImage("menu1_1.png", renderer))
	{
		menu_Run = false;
		quit = true;
	}


	text_item[0].SetText(item);
	text_item[0].SetTextColor(textobject::YELLOW_TYPE);
	text_item[0].ShowText(font_menu, renderer);
	poss_item[0].x = WINDOW_WIDTH / 2 - text_item[0].GetRect().w / 2;
	poss_item[0].y = WINDOW_HEIGHT - 200;
	text_item[0].SetRect(poss_item[0].x, poss_item[0].y);

	text_item[1].SetText("Infor");
	text_item[1].SetTextColor(textobject::YELLOW_TYPE);
	text_item[1].ShowText(font_menu, renderer);
	poss_item[1].x = WINDOW_WIDTH / 2 - text_item[1].GetRect().w / 2;
	poss_item[1].y = WINDOW_HEIGHT - 130;
	text_item[1].SetRect(poss_item[1].x, poss_item[1].y);

	text_item[2].SetText("Exit !");
	text_item[2].SetTextColor(textobject::YELLOW_TYPE);
	text_item[2].ShowText(font_menu, renderer);
	poss_item[2].x = WINDOW_WIDTH / 2 - text_item[2].GetRect().w / 2;
	poss_item[2].y = WINDOW_HEIGHT - 60;
	text_item[2].SetRect(poss_item[2].x, poss_item[2].y);

	text_item[3].SetText("Back !");
	text_item[3].SetTextColor(textobject::YELLOW_TYPE);
	text_item[3].ShowText(font_menu, renderer);
	poss_item[3].x = 10;
	poss_item[3].y = 10;
	text_item[3].SetRect(poss_item[3].x, poss_item[3].y);

	int xm = 0;
	int ym = 0;
	while (menu_Run)
	{
		if (menu_num == 0)
		{
			menu0.Render(renderer);
			text_item[0].ShowText(font_menu, renderer);
			text_item[1].ShowText(font_menu, renderer);
			text_item[2].ShowText(font_menu, renderer);
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
		while (SDL_PollEvent(&e_menu))
		{
			if (e_menu.type == SDL_QUIT)
			{
				menu_Run = false;
				quit = true;
			}
			else if (e_menu.type == SDL_MOUSEMOTION)
			{
				xm = e_menu.motion.x;
				ym = e_menu.motion.y;
				for (int i = 0; i < num_item; i++)
				{
					if (check_mouse_item(xm, ym, text_item[i].GetRect()))
					{
						text_item[i].SetTextColor(textobject::WHILE_TYPE);
					}
					else text_item[i].SetTextColor(textobject::YELLOW_TYPE);
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
							reset();
							menu_Run = false;
						}
						else if (i == 1)
						{
							menu_num = 1;
						}
						else if (i == 2)
						{
							menu_Run = false;
							quit = true;
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
	textTime.SetTextColor(textobject::WHILE_TYPE);
	exp_.Set_Clip();
	ebr_.SetClips();
	srand(time(NULL));

	if (!init())
	{
		return 0;
	}
	else
	{

		std::string level = "Level : ";
		std::string str_ = " : ";
		if (!background.LoadImage("background6.png", renderer))
		{
			return 0;
		}
		if (!space.LoadImage("rocket.png", renderer))
		{
			return 0;
		}
		if (!exp_.LoadImage("exp.png", renderer))
		{
			return 0;
		}
		if (!ebr_.LoadImage("eggbreak_1.png", renderer))
		{
			return 0;
		}
			//Handle_Game
			background.SetRect(0,run);
			// Create_Threat
			for (int i = 0; i < NUM_STONE_THREAT; i++)
			{
				threatstone* stone_threat = new threatstone;
				int stone_rand = rand() % 2 + 1;
				if (stone_rand == 1) { stone_threat->LoadImage("threat_da_80.png", renderer); }
				 else stone_threat->LoadImage("threat_da.png", renderer);
				int Rand = rand() % 1000 + 10;
				stone_threat->SetXY(0, SPEED_THREAT_STONE);
				stone_threat->SetRect(Rand, -i*200);
				stone_threat->SetStatus(true);
				stone_.push_back(stone_threat);
			}

			for (int i = 0; i < NUM_CHIKEN1; i++)
			{
				chickenobject1* chicken = new chickenobject1;
				chicken->LoadImage("chicken.png",renderer);
				chicken->SetClips();
				chicken->SetXY_val(SPEED_CHICKEN, 0);
				if (0 <= i && i <= 9)
				{
					chicken->SetRect(-i * 100, 50);
				}
				else if (10 <= i && i <= 19)
				{
					chicken->SetRect(-i * 100, 130);
				}
				else if (20 <= i && i <= 29)
				{
					chicken->SetRect(-i * 100, 210);
				}
				if (30 <= i && i <= 39 )
				{
					chicken->SetRect(-i * 100, 290);
				}
				if (40 <= i && i <= 49)
				{
					chicken->SetRect(-i * 100, 370);
				}
				chicken->InitBullet(renderer);
				chicken->SetStatus(true);
				chicken_.push_back(chicken);
			}
			
			menu("Play Game");

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
					run += SPEED_RUN;
					background.SetRect(0, run);
					background.Render(renderer);

					for (int i = 0; i < NUM_STONE_THREAT; i++)
					{
						threatstone* stone = stone_.at(i);
						if (stone != NULL)
						{
							if (stone->GetStatus())
							{
								stone->HandleThreatStone();
								stone->ShowStone(renderer);
							}
						}
						
						//checkcollision_bulletofspace_stone
						std::vector<bulletobject*> bull_list = space.GetBulletList();
						for (int i = 0; i < space.GetBulletList().size(); i++)
						{
							bulletobject* BULLET = bull_list.at(i);
							bool col1 = check_collision(BULLET->GetRect(), stone->GetRect());
							if (col1)
							{
								num_stone_died++;
								stone->SetRect(stone->GetRect().x, -WINDOW_HEIGHT);
								stone->SetStatus(false);
								space.RemoveBullet(i);
								if (num_stone_died % 10 == 0)
								{
									gift.SetIsMoveGift(true);
									gift.SetY_val(SPEED_GIFT);
									gift.SetClips();
									gift.SetGiftType(gift.RandomType());
									gift.LoadGift(renderer);
									gift.SetRect(rand()%1000+10, -300);
								}
							}
						}

						//checkcollision_stone_space
						bool col2 = check_collision(stone->GetRect(), space.GetRect());
						if (col2)
						{
							num_stone_died++;
							stone->SetRect(stone->GetRect().x, -WINDOW_HEIGHT);
							stone->SetStatus(false);
							exp_.SetRect(space.GetRect().x, space.GetRect().y);
							exp_.SetFrame(0);
							space.SetRect(-space.GetRect().w, -space.GetRect().h);
						    space.SetStatus(false);
							space.decrease();
							if (bullet_level >= 1)
							{
								bullet_level--;
							}
						}
					}

					if (run+SPEED_RUN >= 0)
					{
						Level++;
						is_run = false;
					}
				}
					else
					{
						background.Render(renderer);
						for (int i = 0; i < NUM_STONE_THREAT; i++)
						{
							threatstone* stone = stone_.at(i);
							if (stone->GetRect().y >= - stone->GetRect().h && stone->GetRect().y <= WINDOW_HEIGHT)
							{
								stone->HandleThreatStone();
								stone->ShowStone(renderer);
								std::vector<bulletobject*> bull_list = space.GetBulletList();
								for (int i = 0; i < space.GetBulletList().size(); i++)
								{
									bulletobject* BULLET = bull_list.at(i);
									bool col1 = check_collision(BULLET->GetRect(), stone->GetRect());
									if (col1)
									{
										num_stone_died++;
										stone->SetRect(stone->GetRect().x, -WINDOW_HEIGHT);
										stone->SetStatus(false);
										space.RemoveBullet(i);
										if (num_stone_died % 10 ==0)
										{
											gift.SetIsMoveGift(true);
											gift.SetY_val(SPEED_GIFT);
											gift.SetClips();
											gift.SetGiftType(gift.RandomType());
											gift.LoadGift(renderer);
											gift.SetRect(rand()%1000+10, 0);
										}
									}
								}

								bool col2 = check_collision(stone->GetRect(), space.GetRect());
								if (col2)
								{
									num_stone_died++;
									stone->SetRect(stone->GetRect().x, -WINDOW_HEIGHT);
									stone->SetStatus(false);
									exp_.SetRect(space.GetRect().x, space.GetRect().y);
									exp_.SetFrame(0);
									space.SetRect(-space.GetRect().w, -space.GetRect().h);
									space.SetStatus(false);
									space.decrease();
									if(bullet_level>= 1)
									{
										bullet_level--;
									}
								}
							}
							
						}

						for (int i = 0;i < NUM_CHIKEN1;i++)
						{
							chickenobject1* chicken_threat = chicken_.at(i);
							if (chicken_threat == NULL)
							{
								return 0;
							}
							else
							{
								chicken_threat->Move();
								chicken_threat->Show(renderer);
								chicken_threat->HandleBullet(renderer);
								//
								std::vector<bulletobject*> bull_list = space.GetBulletList();
								for (int i = 0; i < space.GetBulletList().size(); i++)
								{
									bulletobject* BULLET = bull_list.at(i);
									bool col1 = check_collision(BULLET->GetRect(), chicken_threat->GetRectChicken());
									if (col1)
									{
										num_stone_died++;
										chicken_threat->SetRect(chicken_threat->GetRect().x, -WINDOW_HEIGHT);
										chicken_threat->SetStatus(false);
										space.RemoveBullet(i);
									}
								}
								//
								bool col2 = check_collision(chicken_threat->GetRectChicken(), space.GetRect());
								if (col2)
								{
									chicken_threat->SetRect(chicken_threat->GetRect().x, -WINDOW_HEIGHT);
									chicken_threat->SetStatus(false);
									exp_.SetRect(space.GetRect().x, space.GetRect().y);
									exp_.SetFrame(0);
									space.SetStatus(false);
									space.SetRect(-space.GetRect().w, -space.GetRect().h);
									space.decrease();
									if (bullet_level >= 1)
									{
										bullet_level--;
									}
								}
								//
								std::vector<bulletobject*> bull_list_chick = chicken_threat->GetBulletList();
								for (int i = 0; i < bull_list_chick.size(); i++)
								{
									bulletobject* bullet_Chicken = bull_list_chick.at(i);
									if (!bullet_Chicken->GetIsMove())
									{
										ebr_.SetRect(bullet_Chicken->GetRect().x, WINDOW_HEIGHT - 40);
										ebr_.SetFrame(0);
										while (ebr_.GetFrame() < 40)
										{
											ebr_.Show(renderer);
										}
									}
									bool col3 = check_collision(bullet_Chicken->GetRect(), space.GetRect());
									if (col3)
									{
										exp_.SetRect(space.GetRect().x, space.GetRect().y);
										exp_.SetFrame(0);
										space.SetStatus(false);
										space.SetRect(-space.GetRect().w, -space.GetRect().h);
										space.decrease();
										if (bullet_level >= 1)
										{
											bullet_level--;
										}
									}
								}
							}
						}
					}

				space.Move();
				space.Show(renderer);
                space.HandleBullet(renderer);

				//Handle_GIft
				if (gift.GetIsMoveGift())
				{
					gift.MoveGift();
					gift.Show(renderer);
					bool colgift = check_collision(gift.GetRectGift(), space.GetRect());
					if (colgift)
					{
						gift.SetIsMoveGift(false);
						gift.SetRect(-gift.GetRect().w, -gift.GetRect().h);
						if (gift.GetGiftType() == HEART)
						{
							space.SetHeart(space.GetHeart()+1);
						}
						else if (gift.GetGiftType() == space.get_bul_type() || gift.GetGiftType() == LEVEL_UP)
						{
							if (bullet_level < 3)
							{
								bullet_level++;
							}
						}
						else
						{
							space.set_bul_type(gift.GetGiftType());
						}
					}
				}

				//show explosion
				if (exp_.GetFrame() < 24)
				{
					exp_.RenderExp(renderer);
				}

				//Return _Game
				if (!space.GetStatus())
				{
					if (space.GetHeart() > 0)
					{
						text_return.SetText("Press 'ENTER' to revive !");
						text_return.ShowText(font_return, renderer);
						text_return.SetRect((WINDOW_WIDTH - text_return.GetRect().w) / 2, (WINDOW_HEIGHT - text_return.GetRect().h) / 2);
						text_return.Render(renderer);
					}
					else
					{
						if (time_end_game <= 300)
						{
							time_end_game++;
							text_end.SetText("Game Over !");
							text_end.ShowText(font_end, renderer);
							text_end.SetRect((WINDOW_WIDTH - text_end.GetRect().w) / 2, (WINDOW_HEIGHT - text_end.GetRect().h) / 2);
							text_end.Render(renderer);
						}
						else
						{
							menu("Play Again !");
							menu_Run = true;
							//reset();
						}
					}
				}

				//header
				std::string text_time = "Time : ";
			    Uint32 time = SDL_GetTicks() / 1000;
				std::string time_ = std::to_string(time);
				text_time += time_;
				textTime.SetText(text_time);
				textTime.SetRect(1000, 10);
				textTime.ShowText(font, renderer);
				textTime.Render(renderer);

				std::string Level_ = std::to_string(Level);
				textLevel.SetText(level+Level_);
				textLevel.ShowText(font_Level, renderer);
				textLevel.SetRect(WINDOW_WIDTH / 2 - textLevel.GetRect().w / 2, 10);
				textLevel.Render(renderer);

				std::string num_heart_ = std::to_string(space.GetHeart());
				text_heart.SetText(str_ + num_heart_);
				text_heart.ShowText(font, renderer);
				text_heart.SetRect(60, 10);
				text_heart.Render(renderer);

				skill_heart.LoadImage("skill_heart.png", renderer);
				skill_heart.SetRect(10, 0);
				skill_heart.Render(renderer);
				std::string bullet_lev = std::to_string(bullet_level);
				text_skill.SetText(str_ + bullet_lev);
				text_skill.ShowText(font, renderer);
				text_skill.SetRect(160, 10);
				text_skill.Render(renderer);


				if (is_run)
				{
				stone_small.LoadImage("threat_small_.png", renderer);
				std::string num_threat_ = std::to_string(num_stone_died);
				text_stone_died.SetText(str_ + num_threat_);
				}
				else
				{
					stone_small.LoadImage("kfc.png", renderer);
					std::string num_threat_ = std::to_string(num_chicken_died);
					text_stone_died.SetText(str_ + num_threat_);

				}
				text_stone_died.ShowText(font, renderer);
				text_stone_died.SetRect(290, 10);
				text_stone_died.Render(renderer);
				stone_small.SetRect(240, 0);
				stone_small.Render(renderer);

				SDL_RenderPresent(renderer);

			}
		
	}
		close();
		return 0;
}