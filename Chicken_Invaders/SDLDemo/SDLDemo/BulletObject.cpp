#include"BulletObject.h"

bulletobject::bulletobject()
{
	x_val_ = 0;
	y_val_ = 0;
	is_move = false;
	bullet_type = BLASTER;
}

bulletobject::~bulletobject()
{

}

void bulletobject::LoadBullet(SDL_Renderer* renderer, int bullet_level)
{
	if (bullet_type == BLASTER)
	{
		std::string blaster_str = "blaster" + std::to_string(bullet_level) + ".png";
		LoadImage(blaster_str, renderer);
	}
	else if (bullet_type == NEUTRON)
	{
		std::string neutron_str = "neutron" + std::to_string(bullet_level) + ".png";
		LoadImage(neutron_str, renderer);
	}
	else if (bullet_type == LASER)
	{
		std::string laster_str = "laser" + std::to_string(bullet_level) + ".png";
		LoadImage(laster_str, renderer);
	}
	else if (bullet_type == ROCKET)
	{
		LoadImage("rocket_1.png", renderer);
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
		egg_.LoadImage("eggbreak.png", renderer);
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