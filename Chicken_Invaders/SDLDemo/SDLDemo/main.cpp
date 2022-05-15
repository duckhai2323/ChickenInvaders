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
#include"kfc.h"
#include"IronObject.h"
#include"BossObject.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
baseobject background;
spaceobject space;
explosion exp_;
giftobject gift;
std::vector<threatstone*>stone_;
std::vector<chickenobject1*>chicken_;
std::vector<ironobject*> iron_;
bossobject boss_;

//header
TTF_Font* font = NULL;
textobject textTime;
TTF_Font* font_Level = NULL;
textobject textLevel;
int Level = 1;
textobject text_stone_died;
int num_stone_died = 0;
int num_kfc = 0;
textobject text_skill;
textobject text_heart;
baseobject stone_small;
baseobject skill_heart;

// Menu
bool menu_Run = true;
SDL_Event e_menu;
baseobject menu0;
baseobject menu1;
baseobject menu2;
baseobject optionSpace;
TTF_Font* font_menu = NULL;
int menu_num = 0;
const int num_item = 5;
const int num_option = 5;
SDL_Rect poss_item[num_item];
textobject text_item[num_item];
textobject text_option[num_option];
std::string theOption_ = "0";



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
int run = -(SCREEN_WIDTH * 9);
bool is_run = true;
bool is_run_boss = true;
int chicken_died = 0;
int time_level = 0;

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
				font_menu = TTF_OpenFont("font.ttf", 40);
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
    run = -(SCREEN_WIDTH * 9);
	is_run = true;

	bullet_level = 0;
	space.set_bul_type(BLASTER);
	space.SetRect(WINDOW_WIDTH / 2 - SPACE_WIDTH / 2, WINDOW_HEIGHT / 2 - SPACE_HEIGHT / 2);
	space.SetHeart(MAIN_HEART);
	space.SetXY(0, 0);
	space.SetStatus(true);
	space.SetKfc(0);
	num_stone_died = 0;
	time_end_game = 0;
	space.LoadImage("space0.png", renderer);

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
			chicken_threat->SetRect((i-10) * 100 + WINDOW_WIDTH, 130);
		}
		else if (20 <= i && i <= 29)
		{
			chicken_threat->SetRect(-(i-20) * 100, 210);
		}
		if (30 <= i && i <= 39)
		{
			chicken_threat->SetRect((i-30) * 100+WINDOW_WIDTH, 290);
		}
		if (40 <= i && i <= 49)
		{
			chicken_threat->SetRect(-(i-40) * 100, 370);
		}
		chicken_threat->SetDownBottom(false);
		chicken_threat->SetStatus(true);
		chicken_threat->ResetBUllet();
		chicken_threat->ResetKfc();
	}

	for (int i = 0; i < NUM_IRON; i++)
	{
		ironobject* iron = new ironobject;
		if (i >= 0 && i <= 9)
		{
			iron->SetRect(0, i * -130);
		}
		else if (i >= 10 && i <= 19)
		{
			iron->SetRect(WINDOW_WIDTH - iron->GetRect().w, i * -130);
		}
		else if (i >= 20 && i <= 31)
		{
			iron->SetRect(400, i * -130);
		}
		else if (i >= 32 && i <= 43)
		{
			iron->SetRect(700, i * -130);
		}
		iron->SetHeart(iron_heart);
		iron->SetStatus(true);
		iron->SetIsRun(false);
		iron_.push_back(iron);
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
	if (!menu2.LoadImage("menu2_1.png", renderer))
	{
		menu_Run = false;
	    quit = true;
	}
	if (!optionSpace.LoadImage("space_0.png", renderer))
	{
		menu_Run = false;
		quit = true;
	}

	text_item[0].SetText(item);
	text_item[0].SetTextColor(textobject::BLUE_TYPE);
	text_item[0].ShowText(font_menu, renderer);
	poss_item[0].x = WINDOW_WIDTH / 2 - text_item[0].GetRect().w / 2;
	poss_item[0].y = WINDOW_HEIGHT - 270;
	text_item[0].SetRect(poss_item[0].x, poss_item[0].y);

	text_item[1].SetText("Information");
	text_item[1].SetTextColor(textobject::BLUE_TYPE);
	text_item[1].ShowText(font_menu, renderer);
	poss_item[1].x = WINDOW_WIDTH / 2 - text_item[1].GetRect().w / 2;
	poss_item[1].y = WINDOW_HEIGHT - 200;
	text_item[1].SetRect(poss_item[1].x, poss_item[1].y);

	text_item[2].SetText("Options");
	text_item[2].SetTextColor(textobject::BLUE_TYPE);
	text_item[2].ShowText(font_menu, renderer);
	poss_item[2].x = WINDOW_WIDTH / 2 - text_item[2].GetRect().w / 2;
	poss_item[2].y = WINDOW_HEIGHT - 130;
	text_item[2].SetRect(poss_item[2].x, poss_item[2].y);

	text_item[3].SetText("Exit !");
	text_item[3].SetTextColor(textobject::BLUE_TYPE);
	text_item[3].ShowText(font_menu, renderer);
	poss_item[3].x = WINDOW_WIDTH / 2 - text_item[3].GetRect().w / 2;
	poss_item[3].y = WINDOW_HEIGHT - 60;
	text_item[3].SetRect(poss_item[3].x, poss_item[3].y);

	text_item[4].SetText("Back !");
	text_item[4].SetTextColor(textobject::BLUE_TYPE);
	text_item[4].ShowText(font_menu, renderer);
	poss_item[4].x = 10;
	poss_item[4].y = WINDOW_HEIGHT - 50;
	text_item[4].SetRect(poss_item[4].x, poss_item[4].y);

	text_option[0].SetText("1 : Space_Blue");
	text_option[0].SetTextColor(textobject::BLUE_TYPE);
	text_option[0].ShowText(font_menu, renderer);
	text_option[0].SetRect(80, 150);
	
	text_option[1].SetText("2 : Space_Green");
	text_option[1].SetTextColor(textobject::BLUE_TYPE);
	text_option[1].ShowText(font_menu, renderer);
	text_option[1].SetRect(80, 200);

	text_option[2].SetText("3 : Space_Purple");
	text_option[2].SetTextColor(textobject::BLUE_TYPE);
	text_option[2].ShowText(font_menu, renderer);
	text_option[2].SetRect(80, 250);

	text_option[3].SetText("4 : Space_Pink");
	text_option[3].SetTextColor(textobject::BLUE_TYPE);
	text_option[3].ShowText(font_menu, renderer);
	text_option[3].SetRect(80, 300);

	text_option[4].SetText("5 : Space_Yellow");
	text_option[4].SetTextColor(textobject::BLUE_TYPE);
	text_option[4].ShowText(font_menu, renderer);
	text_option[4].SetRect(80, 350);

	int xm = 0;
	int ym = 0;
	optionSpace.SetRect(520, 150);
	while (menu_Run)
	{
		if (menu_num == 0)
		{
			menu0.Render(renderer);
			text_item[0].ShowText(font_menu, renderer);
			text_item[1].ShowText(font_menu, renderer);
			text_item[2].ShowText(font_menu, renderer);
			text_item[3].ShowText(font_menu, renderer);
			text_item[0].Render(renderer);
			text_item[1].Render(renderer);
			text_item[2].Render(renderer);
			text_item[3].Render(renderer);
		}
		else if (menu_num == 1)
		{
			menu1.Render(renderer);
			text_item[4].ShowText(font_menu, renderer);
			text_item[4].Render(renderer);
		}
		else if (menu_num == 2)
		{
			menu2.Render(renderer);
			text_item[4].ShowText(font_menu, renderer);
			text_option[0].ShowText(font_menu, renderer);
			text_option[1].ShowText(font_menu, renderer);
			text_option[2].ShowText(font_menu, renderer);
			text_option[3].ShowText(font_menu, renderer);
			text_option[4].ShowText(font_menu, renderer);
			text_item[4].Render(renderer);
			text_option[0].Render(renderer);
			text_option[1].Render(renderer);
			text_option[2].Render(renderer);
			text_option[3].Render(renderer);
			text_option[4].Render(renderer);
			optionSpace.Render(renderer);
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
					else text_item[i].SetTextColor(textobject::BLUE_TYPE);
				}

				for (int i = 0; i < num_option; i++)
				{
					if (check_mouse_item(xm, ym, text_option[i].GetRect()))
					{
						text_option[i].SetTextColor(textobject::WHILE_TYPE);
					}
					else text_option[i].SetTextColor(textobject::BLUE_TYPE);
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
							menu_num = 2;
						}
						else if (i == 3)
						{
							menu_Run = false;
							quit = true;
						}
						else if (i == 4)
						{
							menu_num = 0;
						}
					}
				}

				for (int i = 0; i < num_option; i++)
				{
					if (check_mouse_item(xm, ym, text_option[i].GetRect()))
					{
						theOption_ = std::to_string(i);
						optionSpace.LoadImage("space_" + theOption_ + ".png", renderer);
						if (!space.LoadImage("space" + theOption_ + ".png", renderer))
						{
							return ;
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
	boss_.SetCLips();
	srand(time(NULL));

	if (!init())
	{
		return 0;
	}
	else
	{

		std::string level = "Level : ";
		std::string str_ = " : ";
		if (!background.LoadImage("background1.png", renderer))
		{
			return 0;
		}
		if (!exp_.LoadImage("exp_1.png", renderer))
		{
			return 0;
		}
		if(!boss_.LoadImage("boss.png", renderer))
		{
			return 0;
		}
			//Handle_Game
			background.SetRect(0,run);
			boss_.SetRect(WINDOW_WIDTH / 2 - boss_.GetRectBoss().w / 2, 100);
			boss_.SetStatus(true);
			boss_.SetHeart(boss_heart);
			// Create_Threat
			for (int i = 0; i < NUM_STONE_THREAT; i++)
			{
				threatstone* stone_threat = new threatstone;
				int stone_rand = rand() % 3 + 1;
				if (stone_rand == 1) { stone_threat->LoadImage("threat_da_80.png", renderer); }
				else if (stone_rand == 2) { stone_threat->LoadImage("threat_da.png", renderer); }
				else stone_threat->LoadImage("threat_da_boss.png", renderer);
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
				chicken->SetXY_val(SPEED_CHICKEN,SPEED_CHICKEN);
				if (0 <= i && i <= 9)
				{
					chicken->SetRect(-i * 100, 50);
				}
				else if (10 <= i && i <= 19)
				{
					chicken->SetRect((i-10) * 100 + WINDOW_WIDTH, 130);
				}
				else if (20 <= i && i <= 29)
				{
					chicken->SetRect(-(i-20) * 100, 210);
				}
				if (30 <= i && i <= 39 )
				{
					chicken->SetRect( (i-30) * 100 + WINDOW_WIDTH, 290);
				}
				if (40 <= i && i <= 49)
				{
					chicken->SetRect(-(i-40) * 100, 370);
				}
				chicken->InitBullet(renderer);
				chicken->SetStatus(true);
				chicken->InitKfc(renderer);
				chicken_.push_back(chicken);
			}

			for (int i = 0; i < NUM_IRON; i++)
			{
				ironobject* iron = new ironobject;
				iron->SetXY_val_(SPEED_IRON, SPEED_IRON);
				if (i >= 0 && i <= 9)
				{
				    iron->LoadImage("iron1.png", renderer);
					iron->SetRect(0, i * -130);
				}
				else if (i >= 10 && i <= 19)
				{
					iron->LoadImage("iron2.png", renderer);
					iron->SetRect(WINDOW_WIDTH - iron->GetRect().w, i * -130);
				}
				else if (i >= 20 && i <= 31)
				{
					iron->LoadImage("iron0.png", renderer);
					iron->SetRect(400, i * -130);
				}
				else if (i >= 32 && i <= 43)
				{
					iron->LoadImage("iron0.png", renderer);
					iron->SetRect(700, i * -130);
				}
				iron->SetHeart(iron_heart);
				iron->SetStatus(true);
				iron_.push_back(iron);
			}
			
			menu("Save the World");

			while (!quit)
			{
				while (SDL_PollEvent(&e))
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else
					{
						space.InputAction(e, renderer, bullet_level);
						num_kfc = space.GetKfc();
					}
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
							exp_.SetRect(space.GetRect().x - 100, space.GetRect().y-100);
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

					if (run+SPEED_RUN >= -SCREEN_WIDTH*4)
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
									exp_.SetRect(space.GetRect().x-100, space.GetRect().y-100);
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

						if (Level == 2)
						{

							for (int i = 0; i < NUM_CHIKEN1; i++)
							{
								chickenobject1* chicken_threat = chicken_.at(i);
								if (chicken_threat == NULL)
								{
									return 0;
								}
								else
								{
									chicken_threat->MoveLevel2();
									chicken_threat->Show(renderer);
									chicken_threat->HandleBullet(renderer);
									chicken_threat->HandleKfc(renderer);
									//
									std::vector<bulletobject*> bull_list = space.GetBulletList();
									for (int i = 0; i < space.GetBulletList().size(); i++)
									{
										bulletobject* BULLET = bull_list.at(i);
										bool col1 = check_collision(BULLET->GetRect(), chicken_threat->GetRectChicken());
										if (col1)
										{
											if (BULLET->GetBulletType() == ROCKET)
											{
												exp_.SetRect(BULLET->GetRect().x - 20 -100 , BULLET->GetRect().y - 20-100);
												exp_.SetFrame(0);
											}
											else
											{
												space.RemoveBullet(i);
											}
											chicken_died++;
											chicken_threat->SetRect(chicken_threat->GetRect().x, WINDOW_HEIGHT);
											chicken_threat->SetStatus(false);
											if (chicken_died % 20 == 0)
											{
												gift.SetIsMoveGift(true);
												gift.SetY_val(SPEED_GIFT);
												gift.SetClips();
												gift.SetGiftType(gift.RandomType());
												gift.LoadGift(renderer);
												gift.SetRect(rand() % 1000 + 10, 0);
											}
										}
									}
									//
									bool col2 = check_collision(chicken_threat->GetRectChicken(), space.GetRect());
									if (col2)
									{
										chicken_died++;
										chicken_threat->SetRect(chicken_threat->GetRect().x, WINDOW_HEIGHT);
										chicken_threat->SetStatus(false);
										exp_.SetRect(space.GetRect().x-100, space.GetRect().y-100);
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
										bool col3 = check_collision(bullet_Chicken->GetRect(), space.GetRect());
										if (col3)
										{
											bullet_Chicken->SetIsMove(false);
											exp_.SetRect(space.GetRect().x-100, space.GetRect().y-100);
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
									//
									bool col4 = check_collision(chicken_threat->GetRectKfc(), space.GetRect());
									if (col4)
									{
										if (chicken_threat->GetTypeKfc_() == kfcobject::kfc0 || chicken_threat->GetTypeKfc_() == kfcobject::kfc1)
										{
											num_kfc++;
										}
										else if (chicken_threat->GetTypeKfc_() == kfcobject::kfc2)
										{
											num_kfc += 5;
										}
										else if (chicken_threat->GetTypeKfc_() == kfcobject::kfc3)
										{
											num_kfc += 10;
										}
										chicken_threat->RemoveKfc();
									}
								}
							}
						}

						if (chicken_died == NUM_CHIKEN1)
						{
							if (time_level <= 250)
							{
								time_level++;
							}
							else
							{
							    if(Level < 3)
								{
									time_level = 0;
								}
								Level++;
						     	chicken_died = 0;
							}
							if (Level == 3)
							{
								for (int i = 0; i < NUM_CHIKEN1; i++)
								{
									chickenobject1* chicken2 = chicken_.at(i);
									if (i >= 0 && i <= 4)
									{
										chicken2->SetRect(112.5, -i * 80);
									}
									else if (i >= 5 && i <= 9)
									{
										chicken2->SetRect(212.5, -i * 80);
									}
									else if (i >= 10 && i <= 14)
									{
										chicken2->SetRect(312.5, -i * 80);
									}
									else if (i >= 15 && i <= 19)
									{
										chicken2->SetRect(412.5, -i * 80);
									}
									else if (i >= 20 && i <= 24)
									{
										chicken2->SetRect(512.5, -i * 80);
									}
									else if (i >= 25 && i <= 29)
									{
										chicken2->SetRect(612.5, -i * 80);
									}
									else if (i >= 30 && i <= 34)
									{
										chicken2->SetRect(712.5, -i * 80);
									}
									else if (i >= 35 && i <= 39)
									{
										chicken2->SetRect(812.5, -i * 80);
									}
									else if (i >= 40 && i <= 44)
									{
										chicken2->SetRect(912.5, -i * 80);
									}
									else if (i >= 45 && i <= 49)
									{
										chicken2->SetRect(1012.5, -i * 80);
									}
									chicken2->SetDownBottom(false);
									chicken2->SetStatus(true);
									chicken2->ResetBUllet();
									chicken2->ResetKfc();
								}
							}

							if (Level == 4)
							{
								for (int i = 0; i < NUM_CHIKEN1; i++)
								{
									chickenobject1* chicken3 = chicken_.at(i);
									if (i >= 0 && i <= 4)
									{
										chicken3->SetRect(112.5, -i * 80 - 100);
									}
									else if (i >= 5 && i <= 9)
									{
										chicken3->SetRect(212.5, (i-5) * 80+WINDOW_HEIGHT);
									}
									else if (i >= 10 && i <= 14)
									{
										chicken3->SetRect(312.5, -(i-10) * 80);
									}
									else if (i >= 15 && i <= 19)
									{
										chicken3->SetRect(412.5, (i-15) * 80 + WINDOW_HEIGHT);
									}
									else if (i >= 20 && i <= 24)
									{
										chicken3->SetRect(512.5, -(i-20) * 80);
									}
									else if (i >= 25 && i <= 29)
									{
										chicken3->SetRect(612.5, (i-25) * 80 + WINDOW_HEIGHT);
									}
									else if (i >= 30 && i <= 34)
									{
										chicken3->SetRect(712.5, -(i-30) * 80);
									}
									else if (i >= 35 && i <= 39)
									{
										chicken3->SetRect(812.5, (i-35) * 80 + WINDOW_HEIGHT);
									}
									else if (i >= 40 && i <= 44)
									{
										chicken3->SetRect(912.5, -(i-40) * 80);
									}
									else if (i >= 45 && i <= 49)
									{
										chicken3->SetRect(1012.5, (i-45) * 80 + WINDOW_HEIGHT);
									}
									chicken3->SetDownBottom(false);
									chicken3->SetStatus(true);
									chicken3->ResetBUllet();
									chicken3->ResetKfc();
								}
							}

							if (Level == 5)
							{
								for (int i = 0; i < 24; i++)
								{
									chickenobject1* chicken4 = chicken_.at(i);
									chicken4->LoadImage("chicken_1.png", renderer);
									if (i >= 0 && i <= 11)
									{
										chicken4->SetRect(WINDOW_WIDTH / 2 + chicken4->GetRectChicken().w + 20, -i * 80);
									}
									else
									{
										chicken4->SetRect(WINDOW_WIDTH / 2 - chicken4->GetRectChicken().w*2 -20, -(i - 12) * 80);
									}
									chicken4->SetDownBottom(false);
									chicken4->SetStatus(true);
									chicken4->ResetBUllet();
									chicken4->ResetKfc();
								}
							}

						}

						if (Level == 3)
						{
							for (int i = 0; i < NUM_CHIKEN1; i++)
							{
								chickenobject1* chicken2_ = chicken_.at(i);
								int t = i%5;
								chicken2_->MoveLevel3(t);
								chicken2_->Show(renderer);
								chicken2_->HandleBullet(renderer);
								chicken2_->HandleKfc(renderer);
								
								//col1
								std::vector<bulletobject*> bull_list = space.GetBulletList();
								for (int i = 0; i < space.GetBulletList().size(); i++)
								{
									bulletobject* BULLET = bull_list.at(i);
									bool col1 = check_collision(BULLET->GetRect(), chicken2_->GetRectChicken());
									if (col1)
									{
										if (BULLET->GetBulletType() == ROCKET)
										{
											exp_.SetRect(BULLET->GetRect().x - 120, BULLET->GetRect().y - 120);
											exp_.SetFrame(0);
										}
										else
										{
											space.RemoveBullet(i);
										}
										chicken_died++;
										chicken2_->SetRect(chicken2_->GetRect().x, WINDOW_HEIGHT);
										chicken2_->SetStatus(false);
										if (chicken_died % 20 == 0)
										{
											gift.SetIsMoveGift(true);
											gift.SetY_val(SPEED_GIFT);
											gift.SetClips();
											gift.SetGiftType(gift.RandomType());
											gift.LoadGift(renderer);
											gift.SetRect(rand() % 1000 + 10, 0);
										}
									}
								}

								//col2
								bool col2 = check_collision(chicken2_->GetRectChicken(), space.GetRect());
								if (col2)
								{
									chicken_died++;
									chicken2_->SetRect(chicken2_->GetRect().x, WINDOW_HEIGHT);
									chicken2_->SetStatus(false);
									exp_.SetRect(space.GetRect().x-100, space.GetRect().y-100);
									exp_.SetFrame(0);
									space.SetStatus(false);
									space.SetRect(-space.GetRect().w, -space.GetRect().h);
									space.decrease();
									if (bullet_level >= 1)
									{
										bullet_level--;
									}
								}

								//col3
								std::vector<bulletobject*> bull_list_chick = chicken2_->GetBulletList();
								for (int i = 0; i < bull_list_chick.size(); i++)
								{
									bulletobject* bullet_Chicken = bull_list_chick.at(i);
									bool col3 = check_collision(bullet_Chicken->GetRect(), space.GetRect());
									if (col3)
									{
										bullet_Chicken->SetIsMove(false);
										exp_.SetRect(space.GetRect().x-100, space.GetRect().y-100);
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

								//col4
								bool col4 = check_collision(chicken2_->GetRectKfc(), space.GetRect());
								if (col4)
								{
									if (chicken2_->GetTypeKfc_() == kfcobject::kfc0 || chicken2_->GetTypeKfc_() == kfcobject::kfc1)
									{
										num_kfc++;
									}
									else if (chicken2_->GetTypeKfc_() == kfcobject::kfc2)
									{
										num_kfc += 5;
									}
									else if (chicken2_->GetTypeKfc_() == kfcobject::kfc3)
									{
										num_kfc += 10;
									}
									chicken2_->RemoveKfc();
								}
							}
						}

						if (Level == 4)
						{
							for (int i = 0; i < NUM_CHIKEN1; i++)
							{
								chickenobject1* chicken3_ = chicken_.at(i);
								chicken3_->MoveLevel4();
								chicken3_->Show(renderer);
								chicken3_->HandleBullet(renderer);
								chicken3_->HandleKfc(renderer);

								//col1
								std::vector<bulletobject*> bull_list = space.GetBulletList();
								for (int i = 0; i < space.GetBulletList().size(); i++)
								{
									bulletobject* BULLET = bull_list.at(i);
									bool col1 = check_collision(BULLET->GetRect(), chicken3_->GetRectChicken());
									if (col1)
									{
										if (BULLET->GetBulletType() == ROCKET)
										{
											exp_.SetRect(BULLET->GetRect().x - 120, BULLET->GetRect().y - 120);
											exp_.SetFrame(0);
										}
										else
										{
											space.RemoveBullet(i);
										}
										chicken_died++;
										chicken3_->SetRect(chicken3_->GetRect().x, WINDOW_HEIGHT);
										chicken3_->SetStatus(false);
										if (chicken_died % 20 == 0)
										{
											gift.SetIsMoveGift(true);
											gift.SetY_val(SPEED_GIFT);
											gift.SetClips();
											gift.SetGiftType(gift.RandomType());
											gift.LoadGift(renderer);
											gift.SetRect(rand() % 1000 + 10, 0);
										}
									}
								}

								//col2
								bool col2 = check_collision(chicken3_->GetRectChicken(), space.GetRect());
								if (col2)
								{
									chicken_died++;
									chicken3_->SetRect(chicken3_->GetRect().x, WINDOW_HEIGHT);
									chicken3_->SetStatus(false);
									exp_.SetRect(space.GetRect().x-100, space.GetRect().y-100);
									exp_.SetFrame(0);
									space.SetStatus(false);
									space.SetRect(-space.GetRect().w, -space.GetRect().h);
									space.decrease();
									if (bullet_level >= 1)
									{
										bullet_level--;
									}
								}

								//col3
								std::vector<bulletobject*> bull_list_chick = chicken3_->GetBulletList();
								for (int i = 0; i < bull_list_chick.size(); i++)
								{
									bulletobject* bullet_Chicken = bull_list_chick.at(i);
									bool col3 = check_collision(bullet_Chicken->GetRect(), space.GetRect());
									if (col3)
									{
										bullet_Chicken->SetIsMove(false);
										exp_.SetRect(space.GetRect().x-100, space.GetRect().y-100);
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

								//col4
								bool col4 = check_collision(chicken3_->GetRectKfc(), space.GetRect());
								if (col4)
								{
									if (chicken3_->GetTypeKfc_() == kfcobject::kfc0 || chicken3_->GetTypeKfc_() == kfcobject::kfc1)
									{
										num_kfc++;
									}
									else if (chicken3_->GetTypeKfc_() == kfcobject::kfc2)
									{
										num_kfc += 5;
									}
									else if (chicken3_->GetTypeKfc_() == kfcobject::kfc3)
									{
										num_kfc += 10;
									}
									chicken3_->RemoveKfc();
								}
							}
						}
						if (Level == 5)
						{
							if (is_run_boss == true)
							{
								run += SPEED_RUN_SKIP;
								background.SetRect(0, run);
								background.Render(renderer);
								if (run + SPEED_RUN_SKIP >= 0)
								{
									is_run_boss = false;
								}
							}
							else
							{
								background.Render(renderer);

								boss_.Show(renderer);
								for (int i = 0; i < NUM_IRON; i++)
								{
									ironobject* iron1 = iron_.at(i);
									if (i >= 0 && i <= 9)
									{
										iron1->HandleMove1(i);
									}
									else if (i >= 10 && i <= 19)
									{
										int t = i % 9;
										iron1->HandleMove2(t);
									}
									else if (i >= 20 && i <= 31)
									{
										int u = i - 20;
										iron1->HandleMove3(u);
									}
									else if (i >= 32 && i <= 43)
									{
										int u = i - 32;
										iron1->HandleMove4(u);
									}
									iron1->Show(renderer,SDL_FLIP_NONE);

									//check col1
								    std::vector<bulletobject*> bull_list = space.GetBulletList();
									for (int t = 0; t < bull_list.size(); t++)
									{
										bulletobject* BULLET = bull_list.at(t);
										bool col1 = check_collision(BULLET->GetRect(), iron1->GetRect());
										if (col1)
										{
											if (BULLET->GetBulletType() == ROCKET)
											{
												exp_.SetRect(BULLET->GetRect().x - 120, BULLET->GetRect().y - 120);
												exp_.SetFrame(0);
											}
											else
											{
												space.RemoveBullet(t);
											}
											iron1->Deacrase();

											if (iron1->GetHeart() <= 2 && iron1->GetHeart() > 0)
											{
												if (i >= 0 && i <= 9)
												{
													iron1->LoadImage("iron1_1.png", renderer);
												}
												else if (i >= 10 && i <= 19)
												{
													iron1->LoadImage("iron2_1.png", renderer);
												}
												else
												{
													iron1->LoadImage("iron0_1.png", renderer);
												}
											}
											else if (iron1->GetHeart() == 0)
											{
												iron1->SetRect(-iron1->GetRect().w, WINDOW_HEIGHT);
												iron1->SetStatus(false);
											}
										}
									}
								
									//col2
									bool col2 = check_collision(iron1->GetRect(), space.GetRect());
									if (col2)
									{
										iron1->SetStatus(false);
										iron1->SetRect(-iron1->GetRect().w, WINDOW_HEIGHT);
										exp_.SetRect(space.GetRect().x - 100, space.GetRect().y - 100);
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

								for (int i = 0; i < 24; i++)
								{
									chickenobject1* chicken4_ = chicken_.at(i);
									if (0 <= i && i <= 11)
									{
										chicken4_->MoveLevel5_0(i);
									}
									else
									{
										chicken4_->MoveLevel5_1(i-12);
									}
									chicken4_->Show(renderer);
									chicken4_->HandleBullet(renderer);
									chicken4_->HandleKfc(renderer);

									//col1
									std::vector<bulletobject*> bull_list = space.GetBulletList();
									for (int i = 0; i < space.GetBulletList().size(); i++)
									{
										bulletobject* BULLET = bull_list.at(i);
										bool col1 = check_collision(BULLET->GetRect(), chicken4_->GetRectChicken());
										if (col1)
										{
											if (BULLET->GetBulletType() == ROCKET)
											{
												exp_.SetRect(BULLET->GetRect().x - 120, BULLET->GetRect().y - 120);
												exp_.SetFrame(0);
											}
											else
											{
												space.RemoveBullet(i);
											}
											chicken_died++;
											chicken4_->SetRect(chicken4_->GetRect().x, WINDOW_HEIGHT);
											chicken4_->SetStatus(false);
											if (chicken_died % 20 == 0)
											{
												gift.SetIsMoveGift(true);
												gift.SetY_val(SPEED_GIFT);
												gift.SetClips();
												gift.SetGiftType(gift.RandomType());
												gift.LoadGift(renderer);
												gift.SetRect(rand() % 1000 + 10, 0);
											}
										}
									}

									//col2
									bool col2 = check_collision(chicken4_->GetRectChicken(), space.GetRect());
									if (col2)
									{
										chicken_died++;
										chicken4_->SetRect(chicken4_->GetRect().x, WINDOW_HEIGHT);
										chicken4_->SetStatus(false);
										exp_.SetRect(space.GetRect().x - 100, space.GetRect().y - 100);
										exp_.SetFrame(0);
										space.SetStatus(false);
										space.SetRect(-space.GetRect().w, -space.GetRect().h);
										space.decrease();
										if (bullet_level >= 1)
										{
											bullet_level--;
										}
									}

									//col3
									std::vector<bulletobject*> bull_list_chick = chicken4_->GetBulletList();
									for (int i = 0; i < bull_list_chick.size(); i++)
									{
										bulletobject* bullet_Chicken = bull_list_chick.at(i);
										bool col3 = check_collision(bullet_Chicken->GetRect(), space.GetRect());
										if (col3)
										{
											bullet_Chicken->SetIsMove(false);
											exp_.SetRect(space.GetRect().x - 100, space.GetRect().y - 100);
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

									//col4
									bool col4 = check_collision(chicken4_->GetRectKfc(), space.GetRect());
									if (col4)
									{
										if (chicken4_->GetTypeKfc_() == kfcobject::kfc0 || chicken4_->GetTypeKfc_() == kfcobject::kfc1)
										{
											num_kfc++;
										}
										else if (chicken4_->GetTypeKfc_() == kfcobject::kfc2)
										{
											num_kfc += 5;
										}
										else if (chicken4_->GetTypeKfc_() == kfcobject::kfc3)
										{
											num_kfc += 10;
										}
										chicken4_->RemoveKfc();
									}
								}

								//check_col_boss1
								std::vector<bulletobject*> bullet_list = space.GetBulletList();
								for (int t = 0; t < bullet_list.size(); t++)
								{
									bulletobject* BULLET = bullet_list.at(t);
									bool colboss1 = check_collision(boss_.GetRectBoss(), BULLET->GetRect());
									if (colboss1)
									{
										if (BULLET->GetBulletType() == ROCKET)
										{
											exp_.SetRect(BULLET->GetRect().x - 120, BULLET->GetRect().y - 120);
											exp_.SetFrame(0);
										}
										else
										{
											space.RemoveBullet(t);
										}
										boss_.Decrease();
										if (boss_.GetHeart() == 0)
										{
											exp_.SetRect(boss_.GetRect().x - 100, boss_.GetRect().y - 100);
											exp_.SetFrame(0);
											boss_.SetRect(boss_.GetRect().w, WINDOW_HEIGHT);
											boss_.SetStatus(false);
										}

									}

								}
								//check_col_boss2
								bool colboss2 = check_collision(boss_.GetRectBoss(), space.GetRect());
								if (colboss2)
								{
									boss_.Decrease();
									if (boss_.GetHeart() == 0)
									{
										exp_.SetRect(boss_.GetRect().x - 100, boss_.GetRect().y - 100);
										exp_.SetFrame(0);
										boss_.SetRect(boss_.GetRect().w, WINDOW_HEIGHT);
										boss_.SetStatus(false);
									}
									exp_.SetRect(space.GetRect().x - 100, space.GetRect().y - 100);
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

				space.Move();
				space.Show(renderer);
                space.HandleBullet(renderer);
				space.SetKfc(num_kfc);
				


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
				if (exp_.GetFrame() < 54)
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
							reset();
							menu("Play Again !");
							menu_Run = true;
						}
					}
				}
				else
				{
					if (boss_.GetHeart() == 0)
					{
						if (time_end_game <= 300)
						{
							time_end_game++;
							text_end.SetText("Win !!!");
							text_end.ShowText(font_end, renderer);
							text_end.SetRect((WINDOW_WIDTH - text_end.GetRect().w) / 2, (WINDOW_HEIGHT - text_end.GetRect().h) / 2);
							text_end.Render(renderer);
						}
						else
						{
							reset();
							menu("Play Again !");
							menu_Run = true;
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
					std::string num_threat_ = std::to_string(num_kfc);
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