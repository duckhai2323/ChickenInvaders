#ifndef IRON_OBJECT_H_
#define IRON_OBJECT_H_

#include"CommonFunction.h"
#include"BaseObject.h"

class ironobject :public baseobject
{
public:
	ironobject();
	~ironobject();
	void SetXY_val_(const int& x, const int& y)
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
	void SetIsRun(const bool& is_run)
	{
		is_run_ = is_run;
	}
	bool GetIsRun() const { return is_run_; }

	void SetDegrees(const double& degrees)
	{
		degrees_ = degrees;
	}
	double GetDegrees() const { return degrees_; }

	void SetHeart(const int& heart)
	{
		heart_ = heart;
	}
	int GetHeart() const { return heart_; }
	void Deacrase() { heart_--; }

	void HandleMove1(const int& a);
	void HandleMove2(const int& a);
	void HandleMove3(const int& a);
	void HandleMove4(const int& a);
	void Show(SDL_Renderer* renderer,SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	int x_val_;
	int y_val_;
	bool status_;
	int heart_;
	bool is_run_;
	double degrees_;
};

#endif