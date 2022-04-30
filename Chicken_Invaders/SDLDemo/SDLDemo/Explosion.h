#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include"CommonFunction.h"
#include"BaseObject.h"

#define WIDTH_EXP 150
#define HEIGHT_EXP 165
#define NUM_FRAME_EXP 8

class explosion: public baseobject
{
public:
	explosion();
	~explosion();

	void Set_Clip();
	void RenderExp(SDL_Renderer* renderer);
	void SetFrame(const int& frame)
	{
		frame_ = frame;
	}
	int GetFrame() const { return frame_; }

private:
	int frame_;
	SDL_Rect Exp[NUM_FRAME_EXP];
};

#endif