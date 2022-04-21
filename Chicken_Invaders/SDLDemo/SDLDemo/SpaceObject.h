#ifndef SPACE_OBJECT_H_
#define SPACE_OBJECT_H_

#include"CommonFunction.h"
#include"BaseObject.h"
#include"BulletObject.h"

#define SPACE_WIDTH 67
#define SPACE_HEIGHT 62
#define MAIN_SPEED 10

class spaceobject :public baseobject
{
public:
	spaceobject();
	~spaceobject();

	enum BULLET_SPEED
	{
		BLASTER_SPEED = 12,
		NEUTRON_SPEED = 18,
		LASER_SPEED = 30
	};

	void InputAction(SDL_Event e,SDL_Renderer* renderer,int bullet_level);
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

	void SetBulletList(std::vector<bulletobject*> list) { bullet_list_ = list; }
	std::vector<bulletobject*> GetBulletList () const { return bullet_list_; }
	void set_bul_type(const int& bul_type) { bullet_type_ = bul_type; }
	int get_bul_type()const { return bullet_type_; }

	void HandleBullet(SDL_Renderer* renderer);


private:
	int x_val_;
	int y_val_;

	bool status;
	int bullet_type_;
	std::vector<bulletobject*> bullet_list_;
};

#endif