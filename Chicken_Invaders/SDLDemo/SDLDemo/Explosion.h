#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include"CommonFunction.h"
#include"BaseObject.h"

#define WIDTH_EXP 300
#define HEIGHT_EXP 223
#define NUM_FRAME_EXP 27

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