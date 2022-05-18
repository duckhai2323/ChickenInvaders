#include"BulletObject.h"

bulletobject::bulletobject()
{
	x_val_ = 0;
	y_val_ = 0;
	is_move = false;
	bullet_type = BLASTER;
	run_up = false;
}

bulletobject::~bulletobject()
{

}

void bulletobject::LoadBullet(SDL_Renderer* renderer, int bullet_level)
{
	if (bullet_type == BLASTER)
	{
		std::string blaster_str = "image//blaster" + std::to_string(bullet_level) + ".png";
		LoadImage(blaster_str, renderer);
	}
	else if (bullet_type == NEUTRON)
	{
		std::string neutron_str = "image//neutron" + std::to_string(bullet_level) + ".png";
		LoadImage(neutron_str, renderer);
	}
	else if (bullet_type == LASER)
	{
		std::string laster_str = "image//laser" + std::to_string(bullet_level) + ".png";
		LoadImage(laster_str, renderer);
	}
	else if (bullet_type == ROCKET)
	{
		LoadImage("image//rocket_1.png", renderer);
	}
}

void bulletobject::HandleMoveSpace()
{
	rect_.y -= y_val_;
	if (rect_.y + rect_.h <= 0)
	{
		is_move = false;
	}
}

void bulletobject::HandleMoveChicken(SDL_Renderer* renderer)
{
	rect_.y += y_val_;
	if (rect_.y  >= WINDOW_HEIGHT)
	{
		egg_.LoadImage("image//eggbreak.png", renderer);
		egg_.SetRect(this->rect_.x,WINDOW_HEIGHT-30);
		egg_.SetClips();
		egg_.SetFrame(0);
		while (egg_.GetFrame() < 40)
		{
			egg_.Show(renderer);
		}
		is_move = false;
	}
}

void bulletobject::HandleMoveRocket()
{
	rect_.x += x_val_;
	rect_.y -= y_val_;
	if (rect_.y + rect_.h <= 0)
	{
		is_move = false;
	}
}

void bulletobject::HandleMoveBoss(SDL_Rect rect1,SDL_Rect rect2)
{
	if (!run_up)
	{
		rect_.y += y_val_;
		if (rect_.y >= WINDOW_HEIGHT)
		{
			if (rect1.y > rect2.y)
			{
				run_up = true;
			}
			is_move = false;
		}
	}
	else
	{
		rect_.y -= y_val_;
		if (rect_.y <= 0)
		{
			if (rect1.y <= rect2.y)
			{
				run_up = false;
			}
			is_move = false;
		}
	}
}