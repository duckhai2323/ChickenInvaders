#ifndef EEGBREAK_H_
#define EEGBREAK_H_

#include"CommonFunction.h"
#include"BaseObject.h"

#define EGGBREAK_WIDTH 280/8
#define EGGBREAK_HEIGHT 30
#define NUM_EGGBREAK 8

class eggbreak :public baseobject
{
public:
	eggbreak();
	~eggbreak();

	void SetFrame(const int& frame)
	{
		frame_ = frame;
	}
	int GetFrame() const { return frame_; }
	void SetClips();
	void Show(SDL_Renderer* renderer);

private:
	int frame_;
	SDL_Rect clips[NUM_EGGBREAK];
};

#endif

