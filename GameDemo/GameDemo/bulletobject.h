#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include"Common_Function.h"
#include"Base_Object.h"

#define BLASTER_WIDTH 12
#define BLASTER_HEIGHT 40

class bulletobject :public baseobject
{
public:
	bulletobject();
	~bulletobject();

	bool GetMove() const
	{
		return is_move;
	}
	void SetMove(const bool& move)
	{
		is_move = move;
	}

	void HandleMove(const int& x_boder, const int& y_boder);
	void SetWidthHeight(const int& width, const int& height);

private:
	int x_val_;
	int y_val_;
	bool is_move;
};

#endif