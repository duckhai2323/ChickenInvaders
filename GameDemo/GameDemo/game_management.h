#ifndef GAME_MANAGEMENT_H_
#define GAME_MANADEMENT_H_

#include"Common_Function.h"
#include"Base_Object.h"
#include"MainObject.h"
#include"bulletobject.h"


class management
{
public:
	management();
	~management();

	void init(std::string title);
	bool getRunning()
	{
		return is_Runing;
	}
	void handleEvent();
	void handleGame();
	void clean();

private:
	bool is_Runing;
	SDL_Window* window;
	SDL_Renderer* renderer;
	baseobject background;
	mainobject rocket;
	SDL_Event e;

};

#endif