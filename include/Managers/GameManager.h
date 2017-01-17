#pragma once

#include "SharedContext.h"
#include <SFML\Graphics.hpp>
class LockTile;
class Player;
class GameManager
{
public:
	GameManager(SharedContext& sharedContext);
	
	//inline bool isDoorUnlocked() const { return m_doorUnlocked; }
	void update();
	//void unlockDoor(const LockTile& lock, const Player& player);
	void winGame(const LevelManager& levelManager); //Player has won the game
	void endGame();
	void gameOver();

private:
	SharedContext& m_sharedContext;
};