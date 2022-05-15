#include"BossObject.h"

bossobject::bossobject()
{
	x_val_ = 0;
	y_val_ = 0;
	frame_ = 0;
	heart_ = 300;
	status_ = false;
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
	bullet->LoadImage("egg_big.png", renderer);
	bullet->SetY(SPEED_BOSS_BULLET);
	bullet->SetRect(this->rect_.x + BOSS_WIDTH / 2 - bullet->GetRect().w / 2, this->rect_.y + BOSS_HEIGHT + 20);
	bullet->SetIsMove(true);
	bullet_list_boss.push_back(bullet);
}

void bossobject::HandleBullet(SDL_Renderer* renderer)
{
	
}

void bossobject::HandleBoss()
{

}