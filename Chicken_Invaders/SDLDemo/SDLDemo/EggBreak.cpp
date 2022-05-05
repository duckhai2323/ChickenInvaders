#include"EggBreak.h"

eggbreak::eggbreak()
{
	frame_ = 40;
}

eggbreak::~eggbreak()
{

}

void eggbreak::SetClips()
{
	for (int i = 0; i < NUM_EGGBREAK; i++)
	{
		clips[i].x = i * EGGBREAK_WIDTH;
		clips[i].y = 0;
		clips[i].w = EGGBREAK_WIDTH;
		clips[i].h = EGGBREAK_HEIGHT;
	}
}

void eggbreak::Show(SDL_Renderer* renderer)
{
	frame_++;
	SDL_Rect renderQuad = { rect_.x,rect_.y,EGGBREAK_WIDTH,EGGBREAK_HEIGHT };
	SDL_RenderCopy(renderer, b_object, &clips[frame_ / 5], &renderQuad);
}

