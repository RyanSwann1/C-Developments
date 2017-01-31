#include "Game/Game.h"

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
