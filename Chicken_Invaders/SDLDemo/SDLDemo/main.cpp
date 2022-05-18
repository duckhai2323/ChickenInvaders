#include"GameManagament.h"

int main(int arv, char* args[])
{
	gamemanagement game;
	srand(time(NULL));
	game.InitGame();
	game.Menu("Save the World");
	while (!game.GetQuit())
	{
		game.HandleEvent();
		game.HandleGame();
	}
	game.Close();
	return 0;
}