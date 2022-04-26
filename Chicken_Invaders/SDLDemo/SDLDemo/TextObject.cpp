#include"TextObject.h"

textobject::textobject()
{
	rect_.x = 0;
	rect_.y = 0;
	text_color.r = 255;
	text_color.g = 255;
	text_color.b = 255;
}

textobject::~textobject()
{

}

void textobject::SetTextColor(const int& x)
{
	if (x == RED_TYPE)
	{
		text_color = { 255,0,0 };
	}
	else if (x == BLACK_TYPE)
	{
		text_color = { 0,0,0 };
	}
	else if (x == WHILE_TYPE)
	{
		text_color = { 255,255,255 };
	}
}

void textobject::ShowText(TTF_Font* font, SDL_Renderer* renderer)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), text_color);
	if (surface != NULL)
	{
		//SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 170, 170, 170));
		b_object = SDL_CreateTextureFromSurface(renderer, surface);
		rect_.w = surface->w;
		rect_.h = surface->h;
		SDL_FreeSurface(surface);
		//Render(renderer);
	}
}