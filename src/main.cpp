//https://semidtor.wordpress.com/2013/03/29/rapidxml-mini-tutorial/
//https://thebojan.ninja/2015/04/08/high-cohesion-loose-coupling/
#include "Game\Game.h"

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