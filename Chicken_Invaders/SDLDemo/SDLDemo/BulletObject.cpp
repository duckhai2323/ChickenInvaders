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
}

void bulletobject::HandleMoveSpace()
{
	rect_.y -= y_val_;
	if (rect_.y + rect_.h <= 0)
	{
		is_move = false;
	}
}

void bulletobject::HandleMoveChicken()
{
	rect_.y += y_val_;
	if (rect_.y + rect_.h >= WINDOW_HEIGHT)
	{
		is_move = false;
	}
}
