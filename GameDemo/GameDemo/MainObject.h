#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include"Common_Function.h"
#include"Base_Object.h"
#include"Bullet_Object.h"

#define ROCKET_WIDTH 60;
#define ROCKET_HEIGHT 56;

class mainobject :public baseobject
{
public:
	mainobject();
	~mainobject();

	void InputAction(SDL_Event e,SDL_Renderer* renderer);
	void HandleMove();

	void SetBulletList(std::vector<bulletobject*> list)
	{
		bullet_list = list;
	}

	std::vector<bulletobject*> GetList() const
	{
		return bullet_list;
	}
	void RemoveBullet(const int& num);

private:
	int x_val_;
	int y_val_;
	std::vector<bulletobject*> bullet_list;
};

#endif
