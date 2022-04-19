#include"Threat_Object.h"

threatobject::threatobject()
{
	rect_.x = rand() % 1200;
	rect_.y = 0;
	rect_.w = THREAT_STONE_WIDTH/10;
	rect_.h = THREAT_STONE_HEIGHT;
	x_val_ = 0;
	y_val_ = 0;
}

threatobject::~threatobject()
{
	if (bullet_stone_list.size() > 0)
	{
		for (int i = 0; i < bullet_stone_list.size(); i++)
		{
			bulletobject* BULLET_STONE = bullet_stone_list[i];
			if (BULLET_STONE != NULL)
			{
				delete BULLET_STONE;
				BULLET_STONE = NULL;
			}
		}
		bullet_stone_list.clear();
	}
}

void threatobject::HandleMove(const int& x_boder,const int& y_boder)
{
	rect_.y += 5;
	if (rect_.y > WINDOW_HEIGHT)
	{
		rect_.y = -300;
		rect_.x = rand() % 1000;
	}
}

void threatobject::InitBullet(bulletobject* bullet,SDL_Renderer* renderer)
{
	int temp = rand() % 2+1;
	std::string path1, path2;
	path1 = "egg_small25.png";
	path2 = "threat_bom30.png";
	if (temp == 1)
	{
	if (bullet->LoadImage(path1, renderer))
	{
		bullet->SetWidthHeight(25, 32);
		bullet->SetMove(true);
		bullet->SetRect(this->rect_.x + this->rect_.w / 2, this->rect_.y + this->rect_.h + 10);
		bullet_stone_list.push_back(bullet);
	}

	}
	else
	{
		if (bullet->LoadImage(path2, renderer))
		{
			bullet->SetWidthHeight(25, 32);
			bullet->SetMove(true);
			bullet->SetRect(this->rect_.x + this->rect_.w / 2, this->rect_.y + this->rect_.h + 10);
			bullet_stone_list.push_back(bullet);
		}
	}
}

void threatobject::MakeBullet(const int& x_limit, const int& y_limit,SDL_Renderer* renderer)
{
	for (int i = 0; i < bullet_stone_list.size(); i++)
	{
		bulletobject* Bullet = bullet_stone_list.at(i);
		if (Bullet->GetMove())
		{
			Bullet->HandleMoveThreat(WINDOW_WIDTH, WINDOW_HEIGHT);
			Bullet->Render(renderer, NULL);
		}
		else
		{
			Bullet->SetRect(this->rect_.x + this->rect_.w / 2, this->rect_.y + this->rect_.h + 10);
			Bullet->SetMove(true);
		}
	}
}

void threatobject::Reset(const int& y)
{
	rect_.x = rand() % 1000;
	rect_.y = y;

	for (int i = 0; i < bullet_stone_list.size(); i++)
	{
		bulletobject* p_bullet = bullet_stone_list[i];
		if (p_bullet != NULL)
		{
			RetSetBullet(p_bullet);
		}
	}
}
void threatobject::RetSetBullet(bulletobject* bullet)
{
	bullet->SetRect(this->rect_.x + this->rect_.w / 2, this->rect_.y + this->rect_.h + 10);
}