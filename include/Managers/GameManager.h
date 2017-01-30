#pragma once

#include "Managers/StateManager.h"
#include "Managers/EntityManager.h"
#include "Map/WorldMap.h"
#include <SFML/Graphics.hpp>
class Player;
class DoorTile;
class GameManager
{
public:
	GameManager(StateManager& stateManager, WorldMap& worldMap, EntityManager& entityManager);

	void loadNextLevel(const DoorTile& door, const Player& player);
	void endGame();
	void gameOver();

	void draw(sf::RenderWindow& window);
	void update(const float deltaTime);

private:
	StateManager& m_stateManager;
	WorldMap& m_worldMap;
	EntityManager& m_entityManager;
	int m_currentMapIndex;
	const std::vector<std::string> m_mapNames;

	void purgeCurrentLevel();
	std::vector<std::string> loadInMapNames() const;
	inline const std::string& getCurrentLevelName() const { return m_mapNames.at(m_currentMapIndex); }
	inline bool levelsToComplete() const { return m_currentMapIndex < m_mapNames.size(); }

	void winGame(); //Player has won the game
};