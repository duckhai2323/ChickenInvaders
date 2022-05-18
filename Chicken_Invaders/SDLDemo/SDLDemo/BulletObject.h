#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include"CommonFunction.h"
#include"BaseObject.h"
#include"EggBreak.h"

class bulletobject :public baseobject
{
public:
	bulletobject();
	~bulletobject();

	void SetX(const int& x) { x_val_ = x; }
	int GetX() const { return x_val_; }
	void SetY(const int& y) { y_val_ = y; }
	int GetY() const { return y_val_; }

	void SetIsMove(const bool& move) { is_move = move; }
	bool GetIsMove() const { return is_move; }

	void SetRunUp() { run_up = false; }
	bool GetRunUp() const { return run_up; }

	void SetBulletType(const int& type) { bullet_type = type; }
	int GetBulletType() const { return bullet_type; }

	void HandleMoveSpace();
	void LoadBullet(SDL_Renderer* renderer, int bullet_level);

	void HandleMoveChicken(SDL_Renderer* renderer);
	void HandleMoveBoss(SDL_Rect rect1,SDL_Rect rect2);
	void HandleMoveRocket();

private:
	int x_val_;
	int y_val_;
	bool is_move;
	bool run_up;
	int bullet_type;
	eggbreak egg_;
};

#endif

