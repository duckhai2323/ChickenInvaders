#include"MainObject.h"

mainobject::mainobject()
{
	x_val_ = 0;
	y_val_ = 0;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = ROCKET_WIDTH;
	rect_.h = ROCKET_HEIGHT;
}

mainobject::~mainobject()
{
	x_val_ = 0;
	y_val_ = 0;
}

void mainobject::InputAction(SDL_Event e,SDL_Renderer* renderer)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0 )
	{
		if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w)
		{
			y_val_ -= 8;
		}
		else if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s)
		{
			y_val_ += 8;
		}
		else if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d)
		{
			x_val_ += 8;
		}
		else if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a)
		{
			x_val_ -= 8;
		}
		else if (e.key.keysym.sym == SDLK_q)
		{
			bulletobject* bullet = new bulletobject;
			if (!bullet->LoadImage("4tiadodennho.png", renderer))
			{
				std::cout << "NULL";
			}
			else
			{
				//bullet->SetWidthHeight(BLASTER_WIDTH, BLASTER_HEIGHT);
				//bullet->SetRect(this->rect_.x + this->rect_.w / 2, this->rect_.y - 5);
				bullet->SetRect(this->rect_.x + this->rect_.w / 2 - bullet->GetRect().w / 2, this->rect_.y - this->rect_.h);
				bullet->SetMove(true);
				bullet_list.push_back(bullet);
			}
		}
		else if (e.key.keysym.sym == SDLK_e)
		{
			bulletobject* bullet = new bulletobject;
			if (!bullet->LoadImage("3tiaxanhdennho.png", renderer))
			{
				std::cout << "NULL";
			}
			else
			{
				//bullet->SetWidthHeight(BLASTER_WIDTH, BLASTER_HEIGHT);
				bullet->SetRect(this->rect_.x + this->rect_.w / 2 - bullet->GetRect().w / 2, this->rect_.y - this->rect_.h - 10);
				bullet->SetMove(true);
				bullet_list.push_back(bullet);
			}
		}
		else if (e.key.keysym.sym == SDLK_SPACE)
		{
			bulletobject* bullet = new bulletobject;
			if (!bullet->LoadImage("blaster0.png", renderer))
			{
				std::cout << "NULL";
			}
			else
			{
				bullet->SetWidthHeight(BLASTER_WIDTH, BLASTER_HEIGHT);
				//bullet->SetRect(this->rect_.x + this->rect_.w / 2, this->rect_.y - 5);
				bullet->SetRect(this->rect_.x + this->rect_.w / 2 - bullet->GetRect().w / 2, this->rect_.y - 10);
				bullet->SetMove(true);
				bullet_list.push_back(bullet);
			}
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w)
		{
			y_val_ += 8;
		}
		else if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s)
		{
			y_val_ -= 8;
		}
		else if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d)
		{
			x_val_ -= 8;
		}
		else if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a)
		{
			x_val_ += 8;
		}
		
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN)
	{
			bulletobject* bullet = new bulletobject;
			if (!bullet->LoadImage("blaster0.png", renderer))
			{
				std::cout << "NULL";
			}
			else
			{
				bullet->SetWidthHeight(BLASTER_WIDTH, BLASTER_HEIGHT);
				//bullet->SetRect(this->rect_.x + this->rect_.w / 2, this->rect_.y - 5);
				bullet->SetRect(this->rect_.x + this->rect_.w / 2 - bullet->GetRect().w / 2, this->rect_.y-10 );
				bullet->SetMove(true);
				bullet_list.push_back(bullet);
			}
		
	}
}

void mainobject::HandleMove()
{
	rect_.x += x_val_;
	if (rect_.x<0 || rect_.x + rect_.w > WINDOW_WIDTH)
	{
		rect_.x -= x_val_;
	}

	rect_.y += y_val_;
	if (rect_.y<0 || rect_.y + rect_.h > WINDOW_HEIGHT)
	{
		rect_.y -= y_val_;
	}
}

void mainobject::RemoveBullet(const int& num)
{
	int size = bullet_list.size();
	if ( size > 0 && num < size)
	{
		for (int i = 0; i < bullet_list.size(); i++)
		{
			if (num < bullet_list.size())
			{
				bulletobject* bulletRemove = bullet_list.at(num);
				bullet_list.erase(bullet_list.begin() + num);

				if (bulletRemove != NULL)
				{
					delete bulletRemove;
					bulletRemove = NULL;
				}
			}
		}
	}
}