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
	HEART
};

const int LEVEL_UP = 4;
const int NUM_STONE_THREAT = 50;
const int NUM_CHIKEN1 = 50;

const int SPEED_THREAT_STONE = 5;
const int SPEED_CHICKEN = 5;
const int SPEED_CHICKEN_BULLET = 5;
enum BULLET_SPEED
{
	BLASTER_SPEED = 12,
	NEUTRON_SPEED = 18,
	LASER_SPEED = 30
};

const int SPEED_RUN = 3;
const int SPEED_GIFT = 5;

const int space_heart = 5;




#endif
