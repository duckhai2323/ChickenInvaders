#include"ThreatStone.h"

threatstone::threatstone()
{
	rect_.x = rand()%1000 + 10;
	rect_.y = -300;
	rect_.w = STONE_WIDTH;
	rect_.h = STONE_HEIGHT;
	x_val_ = 0;
	y_val_ = 0;
	statusStone = false;
}

threatstone::~threatstone()
{

}

void threatstone::HandleThreatStone()
{
	rect_.y += y_val_;
	if (rect_.y >= WINDOW_HEIGHT)
	{
		rect_.x = rand() % 1000 + 10;
		rect_.y = -300;
	}
}

void threatstone::ShowStone(SDL_Renderer* renderer)
{
	if (statusStone == true)
	{
		Render(renderer);
	}
}