#ifndef THREAT_STONE_H_
#define THREAT_STONE_H_

#include"CommonFunction.h"
#include"BaseObject.h"

#define STONE_WIDTH 149
#define STONE_HEIGHT 123
class threatstone : public baseobject
{
public:
	threatstone();
	~threatstone();

	void SetXY(const int& x, const int& y)
	{
		x_val_ = x;
		y_val_ = y;
	}
	int GetX_val () const { return x_val_; }
	int GetY_val () const { return y_val_; }
	void SetStatus(const bool& status)
	{
		statusStone = status;
	}
	bool GetStatus() const
	{
		return statusStone;
	}

	void HandleThreatStone();
	void ShowStone(SDL_Renderer* renderer);
private:
	int x_val_;
	int y_val_;
	bool statusStone;
};

#endif
