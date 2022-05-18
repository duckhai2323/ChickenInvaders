#ifndef SPACE_OBJECT_H_
#define SPACE_OBJECT_H_

#include"CommonFunction.h"
#include"BaseObject.h"
#include"BulletObject.h"

#define SPACE_WIDTH 67
#define SPACE_HEIGHT 62
#define MAIN_SPEED 10
#define MAIN_HEART 5

class spaceobject :public baseobject
{
public:
	spaceobject();
	~spaceobject();

	void InputAction(SDL_Event e,SDL_Renderer* renderer,int bullet_level,Mix_Chunk* sound_bullet[3],Mix_Chunk* sound_return);
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

	void SetXY(const int& x, const int& y) { x_val_ = x; y_val_ = y; }
	void SetBulletList(std::vector<bulletobject*> list) { bullet_list_ = list; }
	std::vector<bulletobject*> GetBulletList () const { return bullet_list_; }
	void set_bul_type(const int& bul_type) { bullet_type_ = bul_type; }
	int get_bul_type()const { return bullet_type_; }

	void HandleBullet(SDL_Renderer* renderer);
	void RemoveBullet(const int& x);
	void SetHeart(const int& heart) { heart_ = heart; }
	int GetHeart() const { return heart_; }
	void decrease() { heart_--; }

	void SetKfc(const int& kfc_)
	{
		kfc = kfc_;
	}
	int GetKfc() const { return kfc; }

private:
	int x_val_;
	int y_val_;

	bool status;
	int bullet_type_;
	int heart_;
	std::vector<bulletobject*> bullet_list_;

	int kfc;
};

#endif
