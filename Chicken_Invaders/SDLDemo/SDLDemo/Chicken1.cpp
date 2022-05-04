#include"Chicken1.h"

chickenobject1::chickenobject1()
{
	frame_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	status = false;
	runSpeed = false;
}

chickenobject1::~chickenobject1()
{

}

void chickenobject1::SetClips()
{
	for (int i = 0; i <NUM_FRAME_CHICKEN ; i++)
	{
		clips[i].x = i * CHICKEN_WIDTH;
		clips[i].y = 0;
		clips[i].w = CHICKEN_WIDTH;
		clips[i].h = CHICKEN_HEIGHT;
	}
}

void chickenobject1::Show(SDL_Renderer* renderer)
{
	if (status == true)
	{

		frame_++;
		if (frame_ / 3 >= NUM_FRAME_CHICKEN)
		{
			frame_ = 0;
		}
		SDL_Rect rectQuad = { rect_.x,rect_.y,CHICKEN_WIDTH,CHICKEN_HEIGHT };
		SDL_RenderCopy(renderer, b_object, &clips[frame_ / 3], &rectQuad);
	}
}

void chickenobject1::Move()
{
	if (status == true)
	{
		if (runSpeed ==  false)
		{
			rect_.x += x_val_;
			if (rect_.x + CHICKEN_WIDTH >= WINDOW_WIDTH)
			{
				runSpeed = true;
				rect_.x -= x_val_;
			}
		}
		else
		{
			rect_.x -= x_val_;
			if (rect_.x <= 0)
			{
				runSpeed = false;
				rect_.x += x_val_;
			}
		}
	}
}