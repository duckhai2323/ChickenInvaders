#include"BaseObject.h"

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
	clean();
}

bool baseobject::LoadImage(std::string path,SDL_Renderer* renderer)
{
	clean();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadSurface = IMG_Load(path.c_str());
    if (loadSurface != NULL) {
        SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format,0, 0xff, 0xff));
        newTexture = SDL_CreateTextureFromSurface(renderer, loadSurface);
        if (newTexture != NULL) {
            rect_.w = loadSurface->w;
            rect_.h = loadSurface->h;
        }
        SDL_FreeSurface(loadSurface);
    }
    b_object = newTexture;
    return b_object != NULL;
}

void baseobject::Render(SDL_Renderer* renderer)
{
    SDL_Rect renderQuad{ rect_.x, rect_.y, rect_.w, rect_.h };
    SDL_RenderCopy(renderer, b_object,NULL, &renderQuad);
}

void baseobject::clean()
{
    if (b_object != NULL)
    {
        SDL_DestroyTexture(b_object);
        b_object = NULL;
        rect_.x = 0;
        rect_.y = 0;
        rect_.w = 0;
        rect_.h = 0;
    }
}