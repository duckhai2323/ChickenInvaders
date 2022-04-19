#include"Bullet_Object.h"

bulletobject::bulletobject()
{
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
	is_move = false;
}

bulletobject::~bulletobject()
{

}

void bulletobject::HandleMove(const int& x_boder, const int& y_boder)
{
	if (is_move == true)
	{
		rect_.y -= 10;
		if (rect_.y + rect_.h < 0)
		{
			is_move = false;
		}
	}
}

void bulletobject::HandleMoveThreat(const int& x_boder, const int& y_boder)
{
	if (is_move == true)
	{
		rect_.y += 12;
		if (rect_.y > WINDOW_HEIGHT)
		{
			is_move = false;
		}
	}
}