#include"SpaceObject.h"

spaceobject::spaceobject()
{
	rect_.x = (WINDOW_WIDTH - SPACE_WIDTH) / 2;
	rect_.y = (WINDOW_HEIGHT - SPACE_HEIGHT) / 2;
	rect_.w = SPACE_WIDTH;
	rect_.h = SPACE_HEIGHT;
	status = true;
	x_val_ = 0;
	y_val_ = 0;
	bullet_type_ = BLASTER;
	heart_ = MAIN_HEART;
	kfc = 0;
}

spaceobject::~spaceobject()
{

}

void spaceobject::InputAction(SDL_Event e,SDL_Renderer* renderer,int bullet_level,Mix_Chunk* sound_bullet[3],Mix_Chunk* sound_return)
{
	if (status == true)
	{
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
			case SDLK_w:
				y_val_ -= MAIN_SPEED;
				break;

			case SDLK_DOWN:
			case SDLK_s:
				y_val_ += MAIN_SPEED;
				break;

			case SDLK_LEFT:
			case SDLK_a:
				x_val_ -= MAIN_SPEED;
				break;

			case SDLK_RIGHT:
			case SDLK_d:
				x_val_ += MAIN_SPEED;
				break;

			case SDLK_SPACE:
			{
				bulletobject* p_bullet = new bulletobject;
				p_bullet->SetBulletType(bullet_type_);
				if (bullet_type_ == BLASTER)
				{
					Mix_PlayChannel(-1, sound_bullet[BLASTER], 0);
					p_bullet->SetY(BLASTER_SPEED);
				}
				else if (bullet_type_ == NEUTRON)
				{
					Mix_PlayChannel(-1, sound_bullet[NEUTRON], 0);
					p_bullet->SetY(NEUTRON_SPEED);
				}
				else
				{
					Mix_PlayChannel(-1, sound_bullet[LASER], 0);
					p_bullet->SetY(LASER_SPEED);
				}
				p_bullet->LoadBullet(renderer, bullet_level);
				p_bullet->SetRect(this->rect_.x + this->rect_.w / 2 - p_bullet->GetRect().w / 2, this->rect_.y - p_bullet->GetRect().h);
				p_bullet->SetIsMove(true);
				bullet_list_.push_back(p_bullet);
			}
				break;
			case SDLK_RETURN:
				if (kfc >= 40)
				{
					bulletobject* p_bullet1 = new bulletobject;
					p_bullet1->SetX(SPEED_ROCKET);
					p_bullet1->SetY(SPEED_ROCKET + 4);
					p_bullet1->SetBulletType(ROCKET);
					p_bullet1->LoadBullet(renderer, 0);
					p_bullet1->SetRect(this->rect_.x + this->rect_.w - p_bullet1->GetRect().w / 2, this->rect_.y + this->rect_.h / 2 - p_bullet1->GetRect().w / 2 - 20);
					p_bullet1->SetIsMove(true);
					bullet_list_.push_back(p_bullet1);
					kfc -= 40;
					break;
				}
			}
		}
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
			case SDLK_w:
				y_val_ += MAIN_SPEED;
				break;

			case SDLK_DOWN:
			case SDLK_s:
				y_val_ -= MAIN_SPEED;
				break;

			case SDLK_LEFT:
			case SDLK_a:
				x_val_ += MAIN_SPEED;
				break;

			case SDLK_RIGHT:
			case SDLK_d:
				x_val_ -= MAIN_SPEED;
				break;
			}
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
		{
			bulletobject* p_bullet = new bulletobject;
			p_bullet->SetBulletType(bullet_type_);
			if (bullet_type_ == BLASTER)
			{
				Mix_PlayChannel(-1, sound_bullet[BLASTER], 0);
				p_bullet->SetY(BLASTER_SPEED);
			}
			else if (bullet_type_ == NEUTRON)
			{
				Mix_PlayChannel(-1, sound_bullet[NEUTRON], 0);
				p_bullet->SetY(NEUTRON_SPEED);
			}
			else
			{
				Mix_PlayChannel(-1, sound_bullet[LASER], 0);
				p_bullet->SetY(LASER_SPEED);
			}
			p_bullet->LoadBullet(renderer, bullet_level);
			p_bullet->SetRect(this->rect_.x + this->rect_.w / 2 - p_bullet->GetRect().w / 2, this->rect_.y - p_bullet->GetRect().h);
			p_bullet->SetIsMove(true);
			bullet_list_.push_back(p_bullet);
		}
	}
	else
	{
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			if (e.key.keysym.sym == SDLK_RETURN)
			{
				if (heart_ > 0)
				{
					Mix_PlayChannel(-1,sound_return,0);
					x_val_ = 0;
					y_val_ = 0;
					rect_.x = WINDOW_WIDTH / 2 - SPACE_WIDTH / 2;
					rect_.y = WINDOW_HEIGHT - SPACE_HEIGHT - 50;
					status = true;
				}
			}
		}
	}
}

void spaceobject::Move()
{
	if (status == true)
	{
		rect_.x += x_val_;
		if (rect_.x <= 0 || rect_.x + rect_.w >= WINDOW_WIDTH)
		{
			rect_.x -= x_val_;
		}

		rect_.y += y_val_;
		if (rect_.y < 0 || rect_.y + rect_.h >= WINDOW_HEIGHT)
		{
			rect_.y -= y_val_;
		}
	}
}

void spaceobject::Show(SDL_Renderer* renderer)
{
	if (status == true)
	{
		Render(renderer);
	}
}

void spaceobject::HandleBullet(SDL_Renderer* renderer)
{
	for (int i = 0; i < bullet_list_.size(); i++)
	{
		bulletobject* b_bullet = bullet_list_.at(i);
		if (b_bullet != NULL)
		{
			if (b_bullet->GetIsMove())
			{
				if (b_bullet->GetBulletType() == ROCKET)
				{
					b_bullet->HandleMoveRocket();
				}
				else b_bullet->HandleMoveSpace();
				b_bullet->Render(renderer);
			}
			else
			{
				if (b_bullet != NULL)
				{
					bullet_list_.erase(bullet_list_.begin() + i);
					delete b_bullet;
					b_bullet = NULL;
				}
			}
		}
	}
}

void spaceobject::RemoveBullet(const int& x)
{
	for (int i = 0; i < bullet_list_.size(); i++)
	{
		if (x < bullet_list_.size())
		{
			bullet_list_.erase(bullet_list_.begin() + x);
		}
	}
}