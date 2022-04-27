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
	LASER
};

const int LEVEL_UP = 3;
const int NUM_STONE_THREAT = 15;



#endif
