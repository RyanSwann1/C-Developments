#include "Managers/LevelManager.h"
#include "Managers\EntityManager.h"
#include "Map\WorldMap.h"
#include "Managers\GameManager.h"
#include "Tiles\DoorTile.h"
#include "Entities\Player.h"
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>

LevelManager::LevelManager(SharedContext& sharedContext)
	: m_sharedContext(sharedContext),
	m_levelParser(sharedContext),
	m_mapNames(loadInMapNames("Maps.txt")),
	m_currentMapID(0)
{
	loadFirstMap();
}

LevelManager::~LevelManager()
{
	purgeCurrentLevel();
}

//void LevelManager::changeLevel()
//{
//}
//
//void LevelManager::changeLevel(const std::string& newLevelName)
//{	
//	auto cIter = std::find_if(m_levelNames.cbegin(), m_levelNames.cend(), [newLevelName](const std::pair<std::string, std::string>& name) {return name.first == newLevelName; });
//	if (cIter != m_levelNames.cend())
//	{
//		purgeCurrentLevel();
//		m_levelParser.parseLevel(cIter->second);
//	}
//}

void LevelManager::loadNextLevel(const DoorTile & door, const Player & player)
{
	if (door.isOpen() && player.isOnNextLevelTile())
	{
		++m_currentMapID;
		if (m_currentMapID < m_mapNames.size())
		{
			m_levelParser.parseLevel(m_mapNames.at(m_currentMapID));
		}
		else
		{
			m_sharedContext.m_gameManager->winGame(*this);
		}
	}
}

void LevelManager::update(const float deltaTime)
{
	m_sharedContext.m_worldMap.update(deltaTime);
	m_sharedContext.m_entityManager.update(deltaTime);
}

void LevelManager::draw(sf::RenderWindow & window)
{
	m_sharedContext.m_worldMap.draw(window);
	m_sharedContext.m_entityManager.draw(window);
}

void LevelManager::purgeCurrentLevel()
{
	m_sharedContext.m_worldMap.purgeTileLayers();
	m_sharedContext.m_entityManager.purgeEntities();
}

std::vector<std::string> LevelManager::loadInMapNames(const std::string & fileName) const
{
	std::ifstream file(fileName);
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

void LevelManager::loadFirstMap()
{
	m_levelParser.parseLevel(m_mapNames.at(m_currentMapID));
}
