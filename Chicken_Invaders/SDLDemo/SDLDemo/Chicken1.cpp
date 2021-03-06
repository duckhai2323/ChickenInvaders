#include"Chicken1.h"

chickenobject1::chickenobject1()
{
	frame_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	status = false;
	runSpeed = false;
}

chickenobject1::~chickenobject1()
{

}

void chickenobject1::SetClips()
{
	for (int i = 0; i <NUM_FRAME_CHICKEN ; i++)
	{
		clips[i].x = i * CHICKEN_WIDTH;
		clips[i].y = 0;
		clips[i].w = CHICKEN_WIDTH;
		clips[i].h = CHICKEN_HEIGHT;
	}
}

void chickenobject1::Show(SDL_Renderer* renderer)
{
	if (status == true)
	{

		frame_++;
		if (frame_ / 3 >= NUM_FRAME_CHICKEN)
		{
			frame_ = 0;
		}
		SDL_Rect rectQuad = { rect_.x,rect_.y,CHICKEN_WIDTH,CHICKEN_HEIGHT };
		SDL_RenderCopy(renderer, b_object, &clips[frame_ / 3], &rectQuad);
	}
}

void chickenobject1::MoveLevel2()
{
	if (status == true)
	{
		if (runSpeed ==  false)
		{
			rect_.x += x_val_;
			if (rect_.x + CHICKEN_WIDTH >= WINDOW_WIDTH)
			{
				runSpeed = true;
				rect_.x -= x_val_;
			}
		}
		else
		{
			rect_.x -= x_val_;
			if (rect_.x <= 0)
			{
				runSpeed = false;
				rect_.x += x_val_;
			}
		}
	}
}

void chickenobject1::MoveLevel3(const int& a)
{
	if (status == true)
	{
		if (runSpeed == false)
		{
			rect_.y += y_val_;
			if (rect_.y + CHICKEN_HEIGHT >= WINDOW_HEIGHT)
			{
				runSpeed = true;
			}
		}
		else
		{
			if (rect_.y <= 50 + 80 * (a%5))
			{
				rect_.y += 0;
			}
			else
			{
			rect_.y -= y_val_;

			}
		}
	}
}

void chickenobject1::MoveLevel4()
{
	if (status == true)
	{
		if (runSpeed == false)
		{
			rect_.y += y_val_;
			if (rect_.y + CHICKEN_HEIGHT >= WINDOW_HEIGHT)
			{
				runSpeed = true;
			}
		}
		else
		{
			rect_.y -= y_val_;
			if (rect_.y <= 0)
			{
				runSpeed = false;
			}
		}
	}
}

void chickenobject1::MoveLevel5_0(const int& a)
{
	if (status == true)
	{
		if (!runSpeed)
		{
			rect_.y += y_val_;
			if (rect_.y > 60 + (a % 4) * 80)
			{
				runSpeed = true;
			}
		}
		else
		{
			if (a <= 3)
			{
				if (rect_.x >= 250)
				{
					rect_.x -= x_val_;
				}
			}
			else if (4 <= a && a <= 7)
			{
				if (rect_.x >= 340)
				{
					rect_.x -= x_val_;
				}
			}
			else if (8 <= a && a <= 11)
			{
				if (rect_.x >= 430)
				{
					rect_.x -= x_val_;
				}
			}
			else if (12 <= a && a <= 15)
			{
				if (rect_.x >= 520)
				{
					rect_.x -= x_val_;
				}
			}
		}
	}
}

void chickenobject1::MoveLevel5_1(const int& a)
{
	if (status == true)
	{
		if (!runSpeed)
		{
			rect_.y += y_val_;
			if (rect_.y > 60 + (a % 4) * 80)
			{
				runSpeed = true;
			}
		}
		else
		{
			if (a <= 3)
			{
				if (rect_.x <= WINDOW_WIDTH-250 -CHICKEN_WIDTH)
				{
					rect_.x += x_val_;
				}
			}
			else if (4 <= a && a <= 7)
			{
				if (rect_.x <= WINDOW_WIDTH-340 -CHICKEN_WIDTH)
				{
					rect_.x += x_val_;
				}
			}
			else if (8 <= a && a <= 11)
			{
				if (rect_.x <= WINDOW_WIDTH-430 -CHICKEN_WIDTH)
				{
					rect_.x += x_val_;
				}
			}
			else if (12 <= a && a <= 15)
			{
				if (rect_.x <= WINDOW_WIDTH - 520 - CHICKEN_WIDTH)
				{
					rect_.x += x_val_;
				}
			}
		}
	}
}

void chickenobject1::InitBullet(SDL_Renderer* renderer)
{
	int Rand = rand() % 2;
	if (Rand == 1)
	{
		bulletobject* bullet = new bulletobject;
		bullet->LoadImage("image//egg2.png", renderer);
		bullet->SetY(SPEED_CHICKEN_BULLET);
		bullet->SetRect(this->rect_.x + CHICKEN_WIDTH / 2 - bullet->GetRect().w / 2, this->rect_.y + CHICKEN_HEIGHT + 10);
		bullet->SetIsMove(true);
		bullet_list_chicken.push_back(bullet);
	}
}

void chickenobject1::HandleBullet(SDL_Renderer* renderer)
{
	if (status == true)
	{
		for (int i = 0; i < bullet_list_chicken.size(); i++)
		{
			bulletobject* bullet_ = bullet_list_chicken.at(i);
			if (bullet_ != NULL)
			{
				if (bullet_->GetIsMove())
				{
					bullet_->Render(renderer);
					bullet_->HandleMoveChicken(renderer);
				}
				else
				{
					bullet_->SetRect(this->rect_.x + CHICKEN_WIDTH / 2 - bullet_->GetRect().w / 2, this->rect_.y + CHICKEN_HEIGHT + 10);
					bullet_->SetIsMove(true);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < bullet_list_chicken.size(); i++)
		{
			bulletobject* bullet = bullet_list_chicken.at(i);
			if (bullet != NULL)
			{
				bullet->SetRect(this->rect_.x + CHICKEN_WIDTH / 2 - bullet->GetRect().w / 2, this->rect_.y + CHICKEN_HEIGHT + 10);
			}
		}
	}
}

void chickenobject1::ResetBUllet()
{
	for (int i = 0; i < bullet_list_chicken.size(); i++)
	{
		bulletobject* bullet_ = bullet_list_chicken.at(i);
		if (bullet_ != NULL)
		{
			bullet_->SetRect(this->rect_.x + CHICKEN_WIDTH / 2 - bullet_->GetRect().w / 2, this->rect_.y + CHICKEN_HEIGHT + 10);
		}
	}
}

void chickenobject1::InitKfc(SDL_Renderer* renderer)
{
	int Rand = rand() % 4;
	kfc.SetKfcType(Rand);
	kfc.LoadKfc(renderer);
	kfc.SetXY_val(0, SPEED_KFC);
	kfc.SetKfcStatus(true);
}

void chickenobject1::HandleKfc(SDL_Renderer* renderer)
{
	if (status == false)
	{
		if (kfc.GetStatus())
		{
			kfc.Render(renderer);
			kfc.Handle();
		}
		else
		{
			kfc.SetRect((this->rect_.x + CHICKEN_WIDTH / 2 - kfc.GetRect().w / 2), (this->rect_.y + this->rect_.h / 2 - CHICKEN_HEIGHT / 2));
		}
	}
	else
	{
		kfc.SetRect((this->rect_.x + CHICKEN_WIDTH / 2 - kfc.GetRect().w / 2), (this->rect_.y + this->rect_.h / 2 - CHICKEN_HEIGHT / 2));
	}
}

void chickenobject1::ResetKfc()
{
	kfc.SetKfcStatus(true);
	kfc.SetRect((this->rect_.x + CHICKEN_WIDTH / 2 - kfc.GetRect().w / 2), (this->rect_.y + this->rect_.h / 2 - CHICKEN_HEIGHT / 2));
}