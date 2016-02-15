#include"GameManager.h"

#pragma comment(lib,"allegro-5.0.10-monolith-md-debug.lib")


//Main function
int main()
{
	GameManager *game = new GameManager;

	if (game->initialize())
		game->start();

	delete game; 
	return 0;
}