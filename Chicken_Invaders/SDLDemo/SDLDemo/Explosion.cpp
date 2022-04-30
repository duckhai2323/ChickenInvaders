#include"Explosion.h"

explosion::explosion()
{
	frame_ = 24;
}

explosion::~explosion()
{

}

void explosion::Set_Clip()
{
	for (int i = 0; i < NUM_FRAME_EXP; i++)
	{
		Exp[i].x = i * WIDTH_EXP;
		Exp[i].y = 0;
		Exp[i].w = WIDTH_EXP;
		Exp[i].h = HEIGHT_EXP;
	}
}

void explosion::RenderExp(SDL_Renderer* renderer)
{
	frame_++;
	SDL_Rect RenderQuad = { rect_.x,rect_.y,WIDTH_EXP,HEIGHT_EXP};
	SDL_RenderCopy(renderer, b_object, &Exp[frame_ / 3], &RenderQuad);
}