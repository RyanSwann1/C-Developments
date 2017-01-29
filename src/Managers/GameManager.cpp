#include "Managers\GameManager.h"
#include "Tiles\DoorTile.h"
#include "Entities\Player.h"
#include "Parser\LevelParser.h"
#include "Utilities.h"
#include <sstream>
#include <fstream>
#include <assert.h>

GameManager::GameManager(StateManager & stateManager, WorldMap& worldMap, EntityManager& entityManager)
	: m_stateManager(stateManager),
	m_worldMap(worldMap),
	m_entityManager(entityManager),
	m_currentMapIndex(0),
	m_mapNames(loadInMapNames())
{
	parseLevel(*this, worldMap, entityManager, getCurrentLevelName());
}

void GameManager::loadNextLevel(const DoorTile & door, const Player & player)
{
	if (door.isOpen() && player.isOnNextLevelTile())
	{
		++m_currentMapIndex;
		if (m_currentMapIndex < m_mapNames.size())
		{
			parseLevel(*this, m_worldMap, m_entityManager, getCurrentLevelName());
		}
		else
		{
			winGame();
		}
	}
}

void GameManager::winGame()
{
	if (!levelsToComplete())
	{
		m_stateManager.switchTo(StateType::Win);
		m_stateManager.removeState(StateType::Game);
		//http://moonstoneequation.com/a-warning-to-others/
	}
}

void GameManager::endGame()
{
	m_stateManager.switchTo(StateType::MainMenu);
	m_stateManager.removeState(StateType::Game);
}

void GameManager::gameOver()
{
	m_stateManager.switchTo(StateType::GameOver);
	m_stateManager.removeState(StateType::Game);
}

void GameManager::draw(sf::RenderWindow & window)
{
	m_entityManager.draw(window);
	m_worldMap.draw(window);
}

void GameManager::update(const float deltaTime)
{
	m_entityManager.update(deltaTime);
	m_worldMap.update(deltaTime);
}

void GameManager::purgeCurrentLevel()
{
	m_worldMap.purgeTileLayers();
	m_entityManager.purgeEntities();
}

std::vector<std::string> GameManager::loadInMapNames() const
{
	std::ifstream file(Utilities::getMapDetails());
	assert(file.is_open());
	std::vector<std::string> mapNames;
	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream keyStream(line);
		std::string location;
		keyStream >> location;

		mapNames.push_back(location);
	}
	file.close();

	return mapNames;
}