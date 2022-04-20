#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include"CommonFunction.h"

class baseobject
{
public:
	baseobject();
	~baseobject();

	void SetRect(const int& x, const int& y)
	{
		rect_.x = x;
		rect_.y = y;
	}
	SDL_Rect GetRect() const
	{
		return rect_;
	}
	bool LoadImage(std::string path, SDL_Renderer* renderer);
	void Render(SDL_Renderer* renderer);
	void clean();


protected:
	SDL_Rect rect_;
	SDL_Texture* b_object;
};

#endif
