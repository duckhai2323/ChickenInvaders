#include"bulletobject.h"

bulletobject::bulletobject()
{
	x_val_ = 0;
	y_val_ = 0;
	is_move = false;
	rect_.x = 0;
	rect_.y = 0;
}

bulletobject::~bulletobject()
{

}

void bulletobject::HandleMove(const int& x_boder,const int& y_boder)
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

void bulletobject::SetWidthHeight(const int& width, const int& height)
{
	rect_.w = width;
	rect_.h = height;
}