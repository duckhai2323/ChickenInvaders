#include"IronObject.h"

ironobject::ironobject()
{
	x_val_ = 0;
	y_val_ = 0;
	status_ = false;
	heart_ = 5;
	is_run_ = false;
	degrees_ = 0;
}

ironobject::~ironobject()
{

}

void ironobject::HandleMove1(const int& a)
{
	if (status_)
	{
		if (!is_run_)
		{
			rect_.y += y_val_;
			if (rect_.y >= 400)
			{
				is_run_ = true;
				degrees_ = 90;
			}
		}
		else
		{
			rect_.x += x_val_;
			if (rect_.x >= WINDOW_WIDTH) rect_.x = -rect_.h;
		}
	}
}

void ironobject::HandleMove2(const int& a)
{
	if (status_)
	{
		if (!is_run_)
		{
			rect_.y += y_val_;
			if (rect_.y >= 350)
			{
				is_run_ = true;
				degrees_ = 90;
			}
		}
		else
		{
			rect_.x -= x_val_;
			if (rect_.x <= -rect_.h) rect_.x = WINDOW_WIDTH;
		}
	}
}

void ironobject::HandleMove3(const int& a)
{
	if (status_)
	{
		if (!is_run_)
		{
			rect_.y += y_val_;
			if (rect_.y >= 50 + (a%6) * 50)
			{
				is_run_ = true;
				degrees_ = 90;
			}
		}
		else
		{
			if (a <= 5)
			{
				if (rect_.x >= 50)
				{
					rect_.x -= x_val_;
				}
			}
			else
			{
				if (rect_.x >= 150)
				{
					rect_.x -= x_val_;
				}
			}
		}
	}
}

void ironobject::HandleMove4(const int& a)
{
	if (status_)
	{
		if (!is_run_)
		{
			rect_.y += y_val_;
			if (rect_.y >= 50 + (a % 6) * 50)
			{
				is_run_ = true;
				degrees_ = 90;
			}
		}
		else
		{
			if (a <= 5)
			{
				if (rect_.x <= WINDOW_WIDTH - rect_.w -50)
				{
					rect_.x += x_val_ ;
				}
			}
			else
			{
				if (rect_.x <= WINDOW_WIDTH - rect_.w - 150)
				{
					rect_.x += x_val_ ;
				}
			}
		}
	}
}

void ironobject::Show(SDL_Renderer* renderer,SDL_RendererFlip flip)
{
	if (status_)
	{
		SDL_Rect renderQuad = { rect_.x,rect_.y,rect_.w,rect_.h };
		SDL_RenderCopyEx(renderer, b_object, NULL, &renderQuad, degrees_, NULL,flip);
	}
}