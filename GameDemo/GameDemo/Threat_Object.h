#ifndef THREAT_OBJECT_
#define THREAT_OBJECT_H_

#include"Common_Function.h"
#include"Base_Object.h"
#include"Bullet_Object.h"

#define THREAT_STONE_WIDTH 1118
#define THREAT_STONE_HEIGHT 90
class threatobject:public baseobject
{
public:
	threatobject();
	~threatobject();
	void SetXY_val(const int& x, const int& y)
	{
		x_val_ = x;
		y_val_ = y;
	}
	int GetX_val() const
	{
		return x_val_;
	}
	int GetY_val() const
	{
		return y_val_;
	}

	void HandleMove(const int& x_boder, const int& y_boder);

	void InitBullet(bulletobject* bullet,SDL_Renderer* renderer);
	void SetBullet_Stone(std::vector<bulletobject*> list)
	{
		bullet_stone_list = list;
	}
	std::vector<bulletobject*> GetStoneList() const
	{
		return bullet_stone_list;
	}
	void MakeBullet(const int& x_limit, const int& y_limit,SDL_Renderer* renderer);

	void Reset(const int &y);
	void RetSetBullet(bulletobject* bullet);
private:
	int x_val_;
	int y_val_;
	std::vector<bulletobject*> bullet_stone_list;
};

#endif
