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
}

spaceobject::~spaceobject()
{

}

void spaceobject::InputAction(SDL_Event e)
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
			}
		}
		if (e.type == SDL_KEYUP && e.key.repeat == 0)
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