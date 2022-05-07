#ifndef CHICKEN_1_H_
#define CHICKEN_1_H_

#include"CommonFunction.h"
#include"BaseObject.h"
#include"BulletObject.h"
#include"kfc.h"

#define CHICKEN_WIDTH 75
#define CHICKEN_HEIGHT 68
#define NUM_FRAME_CHICKEN 18

class chickenobject1 :public baseobject
{
public:
	chickenobject1();
	~chickenobject1();

	void SetXY_val(const int& x, const int& y)
	{
		x_val_ = x;
		y_val_ = y;
	}
	int GetX_val() const { return x_val_; }
	int GetY_val() const { return y_val_; }

	void MoveLevel2();
	void Show(SDL_Renderer* renderer);
	void SetClips();

	void SetStatus(const bool& s)
	{
		status = s;
	}
	void SetDownBottom(const bool& down)
	{
		runSpeed = down;
	}

	bool GetStatus() const { return status; }
	bool GetDownBottom() const { return runSpeed; }

	SDL_Rect GetRectChicken() const
	{
		SDL_Rect rect;
		rect.x = rect_.x;
		rect.y = rect_.y;
		rect.w = CHICKEN_WIDTH;
		rect.h = CHICKEN_HEIGHT;
		return rect;
	}

	void SetBulletList(std::vector<bulletobject*> b_list)
	{
		bullet_list_chicken = b_list;
	}
	std::vector<bulletobject*> GetBulletList() const { return bullet_list_chicken; }

	void InitBullet(SDL_Renderer* renderer);
	void HandleBullet(SDL_Renderer* renderer);
	void ResetBUllet();

	int GetTypeKfc_() const { return kfc.GetKfcType(); }
	void InitKfc(SDL_Renderer* renderer);
	void HandleKfc(SDL_Renderer* renderer);
	SDL_Rect GetRectKfc() const
	{
		return kfc.GetRect();
	}
	void RemoveKfc()
	{
		kfc.SetKfcStatus(false);
	}
	void ResetKfc();
private:
	int x_val_;
	int y_val_;

	int frame_;
	SDL_Rect clips[NUM_FRAME_CHICKEN];
	bool status;
	bool runSpeed;

	std::vector<bulletobject*> bullet_list_chicken;

	kfcobject kfc;
};

#endif