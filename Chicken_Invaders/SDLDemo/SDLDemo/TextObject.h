#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include"CommonFunction.h"
#include"BaseObject.h"

class textobject :public baseobject
{
public:
	enum TYPE_COLOR
	{
		RED_TYPE,
		BLACK_TYPE,
		WHILE_TYPE
	};

	textobject();
	~textobject();
	void SetText(const std::string text_)
	{
		text = text_;
	}

	void SetTextColor(const int& x);
	void ShowText(TTF_Font* font, SDL_Renderer* renderer);

private:
	std::string text;
	SDL_Color text_color;
};

#endif

