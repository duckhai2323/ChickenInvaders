#include"GiftObject.h"

giftobject::giftobject()
{
	gift_type = BLASTER;
	is_move_gift = false;
	frame = 0;
}

giftobject::~giftobject()
{

}

void giftobject::LoadGift(SDL_Renderer* renderer)
{
	if (gift_type == BLASTER)
	{
		LoadImage("gift1.png", renderer);
	}
	else 	if (gift_type == NEUTRON)
	{
		LoadImage("gift2.png", renderer);
	}
	else 	if (gift_type == LASER)
	{
		LoadImage("gift3.png", renderer);
	}
	else if (gift_type == LEVEL_UP)
	{
		LoadImage("gift4.png", renderer);
	}
}

void giftobject::SetClips()
{
	for (int i = 0; i < 25; i++)
	{
		clips_level[i].x = i * LEVEL_UP_WIDTH;
		clips_level[i].y = 0;
		clips_level[i].w = LEVEL_UP_WIDTH;
		clips_level[i].h = LEVEL_UP_HEIGHT;
	}
}

void giftobject::Show(SDL_Renderer* renderer)
{
	if (gift_type < 3)
	{
		if (is_move_gift == true)
		{
			Render(renderer);
		}
	}
	else
	{
		if (is_move_gift == true)
		{
			SDL_Rect renderQuad{ rect_.x, rect_.y,LEVEL_UP_WIDTH, LEVEL_UP_HEIGHT };
			SDL_RenderCopy(renderer, b_object, &clips_level[frame / 4], &renderQuad);
			frame++;
			if (frame / 4 >= 25)
			{
				frame = 0;
			}
		}
	}
}

void giftobject::MoveGift()
{
	if (is_move_gift == true)
	{
		rect_.y += y_val_;
		if (rect_.y > WINDOW_HEIGHT)
		{
			is_move_gift = false;
			rect_.x = -GIFT_WIDTH;
			rect_.y = -GIFT_HEIGHT;
		}
	}
}

int giftobject::RandomType()
{
	int rand_gift_type = rand() % 6;
	rand_gift_type = rand_gift_type < 3 ? rand_gift_type : 3;
	return rand_gift_type;
}