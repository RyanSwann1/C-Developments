//https://semidtor.wordpress.com/2013/03/29/rapidxml-mini-tutorial/

#include "Game\Game.h"
#include <iostream>

int main()
{
	Game game;
	while (game.isRunning())
	{
		game.update();
		game.draw();
		game.lateUpdate();
	}

	return 0;
}