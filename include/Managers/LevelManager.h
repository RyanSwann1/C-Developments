#pragma once

#include "Parser/LevelParser.h"
#include "SharedContext.h"
#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>

class DoorTile;
class Player;
class LevelManager
{
public:
	LevelManager(SharedContext& sharedContext);
	~LevelManager();

	inline bool levelsToComplete() const { return m_currentMapID < m_mapNames.size(); }

	void loadNextLevel(const DoorTile& door, const Player& player);

	void update(const float deltaTime);
	void draw(sf::RenderWindow& window);

private:
	LevelParser m_levelParser;
	SharedContext& m_sharedContext;
	const std::vector<std::string> m_mapNames;
	std::vector<std::string> loadInMapNames(const std::string& fileName) const;
	void purgeCurrentLevel();
	
	int m_currentMapID;
	void loadFirstMap();
};
