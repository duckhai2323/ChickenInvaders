#include"Base_Object.h"

baseobject::baseobject()
{
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
	b_object = NULL;	
}

baseobject::~baseobject()
{
	close();
}

bool baseobject::LoadImage(std::string path, SDL_Renderer* renderer)
{
	close();
	SDL_Surface* surface = IMG_Load(path.c_str());
	SDL_Texture* newtexture = NULL;
	if (surface != NULL)
	{
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xff, 0xff));
		newtexture = SDL_CreateTextureFromSurface(renderer, surface);
		if (newtexture != NULL)
		{
			rect_.w = surface->w;
			rect_.h = surface->h;
			SDL_FreeSurface(surface);
		}
	}
	b_object = newtexture;
	return b_object != NULL;
}

void baseobject::Render(SDL_Renderer* renderer, SDL_Rect* clips)
{
	SDL_Rect renderQuad = { rect_.x,rect_.y,rect_.w,rect_.h };
	SDL_RenderCopy(renderer, b_object, clips, &renderQuad);
}

void baseobject::RenderClip(SDL_Renderer* renderer, SDL_Rect* clips)
{
	SDL_Rect renderQuad = { rect_.x,rect_.y,rect_.w/10,rect_.h };
	SDL_RenderCopy(renderer, b_object, clips, &renderQuad);
}

void baseobject::close()
{
    SDL_DestroyTexture(b_object);
    b_object = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
	rect_.h = 0;
}