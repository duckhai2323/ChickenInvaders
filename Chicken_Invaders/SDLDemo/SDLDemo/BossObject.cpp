#include"BossObject.h"

bossobject::bossobject()
{
	x_val_ = 0;
	y_val_ = 0;
	frame_ = 0;
	heart_ = 300;
	status_ = false;
	handle.turn_left = 0;
	handle.turn_down = 0;
	handle.turn_right = 0;
	handle.turn_up = 0;
}

bossobject::~bossobject()
{

}

void bossobject::SetCLips()
{
	for (int i = 0; i < NUM_FRAME_BOSS; i++)
	{
		Clips[i].x = i * BOSS_WIDTH;
		Clips[i].y = 0;
		Clips[i].w = BOSS_WIDTH;
		Clips[i].h = BOSS_HEIGHT;
	}
}

void bossobject::Show(SDL_Renderer* renderer)
{
	if (status_)
	{
		frame_++;
		if (frame_ / 4 >= NUM_FRAME_BOSS)
		{
			frame_ = 0;
		}
		SDL_Rect renderQuad = { rect_.x,rect_.y,BOSS_WIDTH,BOSS_HEIGHT };
		SDL_RenderCopy(renderer, b_object, &Clips[frame_ / 4], &renderQuad);
	}
}

void bossobject::InitBullet(SDL_Renderer* renderer)
{
	bulletobject* bullet = new bulletobject;
	bullet->LoadImage("image//iron3"+std::to_string(rand()%4)+".png", renderer);
	bullet->SetY(SPEED_BOSS_BULLET);
	bullet->SetRect(this->rect_.x + BOSS_WIDTH / 2 - bullet->GetRect().w / 2, this->rect_.y + BOSS_HEIGHT / 2 - bullet->GetRect().h / 2);
	bullet->SetIsMove(true);
	bullet_list_boss.push_back(bullet);
}

void bossobject::HandleBullet(SDL_Renderer* renderer, SDL_Rect rect1, SDL_Rect rect2)
{
	if (status_ == true)
	{
		for (int i = 0; i < bullet_list_boss.size(); i++)
		{
			bulletobject* bullet_ = bullet_list_boss.at(i);
			if (bullet_ != NULL)
			{
				if (bullet_->GetIsMove())
				{
					bullet_->Render(renderer);
					bullet_->HandleMoveBoss(rect1,rect2);
				}
				else
				{
					bullet_->SetRect(this->rect_.x + BOSS_WIDTH / 2 - bullet_->GetRect().w / 2, this->rect_.y + BOSS_HEIGHT / 2 - bullet_->GetRect().h / 2);
					bullet_->SetIsMove(true);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < bullet_list_boss.size(); i++)
		{
			bulletobject* bullet = bullet_list_boss.at(i);
			if (bullet != NULL)
			{
				bullet->SetRect(this->rect_.x + BOSS_WIDTH / 2 - bullet->GetRect().w / 2, this->rect_.y + BOSS_HEIGHT/2 - bullet->GetRect().h/2);
			}
		}
	}
}

void bossobject::HandleBoss()
{
	if (status_)
	{
		if (handle.turn_down)
		{
			rect_.y += y_val_;
		}
		if (handle.turn_left) {
			rect_.x -= x_val_;
		}
		if (handle.turn_right) {
			rect_.x += x_val_;
		}
		if (handle.turn_up) {
			rect_.y -= y_val_;
		}
		if (rect_.y >= WINDOW_HEIGHT - BOSS_HEIGHT) {
			handle.turn_up = 1;
			handle.turn_down = 0;
		}
		else if (rect_.y <= 0) {
			handle.turn_down = 1;
			handle.turn_up = 0;
		}
		if (rect_.x <= 0) {
			handle.turn_right = 1;
			handle.turn_left = 0;
		}
		else if (rect_.x >= WINDOW_WIDTH - BOSS_WIDTH) {
			handle.turn_left = 1;
			handle.turn_right = 0;
		}
	}
}

void bossobject::ShowHeart(SDL_Renderer* renderer,const int& w)
{
	if (status_)
	{
		SDL_Rect renderQuad = { rect_.x + BOSS_WIDTH / 2 - boss_heart,rect_.y - 20, w*2,6 };
		SDL_Rect renderQuad0 = { rect_.x + BOSS_WIDTH / 2 - boss_heart,rect_.y - 20, boss_heart*2,6 };
		SDL_SetRenderDrawColor(renderer, 220, 220, 220, 0.3);
		SDL_RenderFillRect(renderer, &renderQuad0);
		w <= 20 ? SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0.5) : SDL_SetRenderDrawColor(renderer, 173, 255, 47, 0.5);
		SDL_RenderFillRect(renderer, &renderQuad);
	}
}