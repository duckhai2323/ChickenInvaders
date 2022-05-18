#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 750;

const int SCREEN_WIDTH = 750;

enum Bullet_Level
{
	BLASTER,
	NEUTRON,
	LASER,
	HEART,
	ROCKET  =  5 
};

const int LEVEL_UP = 4;
const int NUM_STONE_THREAT = 50;
const int NUM_CHIKEN1 = 50;
const int NUM_IRON = 44;
const int NUM_BOSS = 2;

const int SPEED_THREAT_STONE = 5;
const int SPEED_CHICKEN = 5;
const int SPEED_CHICKEN_BULLET = 3;
const int SPEED_BOSS_BULLET = 10;
const int SPEED_KFC = 6;
const int SPEED_IRON = 10;
const int SPEED_BOSS = 5;
enum BULLET_SPEED
{
	BLASTER_SPEED = 12,
	NEUTRON_SPEED = 18,
	LASER_SPEED = 30
};
const int SPEED_ROCKET = 2;

const int SPEED_RUN = 2;
const int SPEED_RUN_SKIP = 20;
const int SPEED_GIFT = 5;

const int space_heart = 5;
const int iron_heart = 5;
const int boss_heart = 50;

struct bossStatus
{
	int turn_right;
	int turn_left;
	int turn_down;
	int turn_up;
};


#endif
