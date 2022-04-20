#ifndef SPACE_OBJECT_H_
#define SPACE_OBJECT_H_

#include"CommonFunction.h"
#include"BaseObject.h"

#define SPACE_WIDTH 67
#define SPACE_HEIGHT 62
#define MAIN_SPEED 10

class spaceobject :public baseobject
{
public:
	spaceobject();
	~spaceobject();

	void InputAction(SDL_Event e);
	void Move();
	void Show(SDL_Renderer* renderer);

	void SetStatus(const bool& status_)
	{
		status = status_;
	}
	bool GetStatus() const
	{
		return status;
	}

private:
	int x_val_;
	int y_val_;

	bool status;
};

#endif
