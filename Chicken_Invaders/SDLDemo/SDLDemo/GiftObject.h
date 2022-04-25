#ifndef GIFT_OBJECT_H_
#define GIFT_OBJECT_H_

#include"CommonFunction.h"
#include"BaseObject.h"

#define GIFT_WIDTH 49
#define GIFT_HEIGHT 58
#define LEVEL_UP_WIDTH 49
#define LEVEL_UP_HEIGHT 51
#define GIFT_SPEED 3

class giftobject :public baseobject
{
public:
	giftobject();
	~giftobject();

	void SetX_val(const int& x_val)
	{
		x_val_ = x_val;
	}
	void SetY_val(const int& y_val)
	{
		y_val_ = y_val;
	}
	int GetX_val() const { return x_val_; }
	int GetY_val() const { return y_val_; }

	void SetIsMoveGift(const bool& is_move) { is_move_gift = is_move; }
	bool GetIsMoveGift() const { return is_move_gift; }

	void SetGiftType(const int& x) { gift_type = x; }
	int GetGiftType() const { return gift_type; }

	void LoadGift(SDL_Renderer* renderer);
	void Show(SDL_Renderer* renderer);
	void MoveGift();
	void SetClips();
	int RandomType();

private:
	int x_val_;
	int y_val_;

	bool is_move_gift;
	int gift_type;
	int frame;
	SDL_Rect clips_level[25];
};

#endif

