#ifndef BOSS_OBJECT_H_
#define BOSS_OBJECT_H_

#include"BaseObject.h"
#include"CommonFunction.h"
#include"BulletObject.h"

#define BOSS_WIDTH 200
#define BOSS_HEIGHT 160
#define NUM_FRAME_BOSS 10

class bossobject :public baseobject
{
public:
	bossobject();
	~bossobject();

	void SetXY_val(const int& x, const int& y)
	{
		x_val_ = x;
		y_val_ = y;
	}
	int GetX_val() const { return x_val_; }
	int GetY_val() const { return y_val_; }

	void SetStatus(const bool& status)
	{
		status_ = status;
	}
	bool GetStatus() const { return status_; }

	SDL_Rect GetRectBoss() const
	{
		SDL_Rect Size;
		Size.x = rect_.x;
		Size.y = rect_.y;
		Size.w = BOSS_WIDTH;
		Size.h = BOSS_HEIGHT;
		return Size;
	}

	void SetCLips();
	void Show(SDL_Renderer* renderer);
	void HandleBoss();

	std::vector<bulletobject*> GetBulletList() const
	{
		return bullet_list_boss;
	}
	void InitBullet(SDL_Renderer* renderer);
	void HandleBullet(SDL_Renderer* renderer);


	void SetHeart(const int& heart)
	{
		heart_ = heart;
	}
	int GetHeart() const { return heart_; }
	void Decrease() { heart_--; }

private:
	int x_val_;
	int y_val_;
	int frame_;
	bool status_;
	std::vector<bulletobject*> bullet_list_boss;
	SDL_Rect Clips[NUM_FRAME_BOSS];
	int heart_;
};

#endif

