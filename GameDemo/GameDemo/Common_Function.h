#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include <cstdlib>
#include <ctime>

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;
const int NUM_THREAT = 5;
const int SCREEN_BACKGROUND = 800;
const int NUM_ANIMATION = 10;

bool CheckCollistion(const SDL_Rect& object1, const  SDL_Rect& object2);
#endif
