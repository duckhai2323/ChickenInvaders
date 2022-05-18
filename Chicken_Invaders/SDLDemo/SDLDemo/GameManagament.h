#ifndef GAME_MANAGEMENT_H_
#define GAME_MANAGEMENT_H_

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

class gamemanagement
{
public:
	gamemanagement();
	~gamemanagement();
	void InitGame();
	bool check_collision(const SDL_Rect& object1, const SDL_Rect& object2);
	bool check_mouse_item(const int& x, const int& y, const SDL_Rect& rect);
	void Menu(const std::string& item);
	void HandleChicken();
	void ResetGame();
	void HandleEvent();
	void HandleGame();
	bool GetQuit() const { return quit; }
	void Close();
private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	baseobject background;
	baseobject circle;
	spaceobject space;
	explosion exp_;
	giftobject gift;
	std::vector<threatstone*>stone_;
	std::vector<chickenobject1*>chicken_;
	std::vector<ironobject*> iron_;
	std::vector<bossobject*> boss_;

	//header
	TTF_Font* font = NULL;
	textobject textTime;
	TTF_Font* font_Level = NULL;
	textobject textLevel;
	int Level;
	textobject text_stone_died;
	int num_stone_died;
	int num_kfc;
	textobject text_skill;
	textobject text_heart;
	baseobject stone_small;
	baseobject skill_heart;
	int theOption ;

	// Menu
	bool menu_Run = true;
	SDL_Event e_menu;
	baseobject menu0;
	baseobject menu1;
	baseobject menu2;
	baseobject optionSpace;
	baseobject tick;
	TTF_Font* font_menu = NULL;
	int menu_num ;
	SDL_Rect poss_item[num_item];
	textobject text_item[num_item];
	textobject text_option[num_option];
	std::string theOption_;



	//Return_Game_End_Game
	TTF_Font* font_return = NULL;
	textobject text_return;
	TTF_Font* font_end = NULL;
	textobject text_end;
	int time_end_game;

	//music
	Mix_Music* music_start = NULL;
	Mix_Chunk* sound_click = NULL;
	Mix_Chunk* sound_bullet[3];
	Mix_Chunk* sound_exp;
	Mix_Chunk* sound_expRocket;
	Mix_Chunk* sound_chicken[2];
	Mix_Chunk* sound_expBoss;
	Mix_Chunk* sound_stone;
	Mix_Chunk* sound_kfc;
	Mix_Chunk* sound_iron;

	//Handle_Game
	SDL_Event e;
	bool quit ;
	int bullet_level ;
	int run ;
	bool is_run ;
	bool is_run_boss ;
	int chicken_died ;
	int boss_died ;
	int iron_died ;
	int time_level ;
	std::string level;
	std::string str_;
};

#endif

