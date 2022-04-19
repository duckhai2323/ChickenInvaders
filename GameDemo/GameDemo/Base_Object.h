#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include"Common_Function.h"

class baseobject
{
public:
	baseobject();
	~baseobject();

	bool LoadImage(std::string path, SDL_Renderer* renderer);

	void SetRect(const int& x, const int& y)
	{
		rect_.x = x;
		rect_.y = y;
	}
	SDL_Rect GetRect() const
	{
		return rect_;
	}

	void Render(SDL_Renderer* renderer,SDL_Rect* clips);
	void RenderClip(SDL_Renderer* renderer, SDL_Rect* clips);
	void close();

protected:
	SDL_Rect rect_;
	SDL_Texture* b_object;
};

#endif
