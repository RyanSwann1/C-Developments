#include "Tiles/CoinTile.h"
#include "Entities/Player.h"
#include "Map/WorldMap.h"
#include "Utilities.h"
#include <fstream>
#include <sstream>
#include <assert.h>

CoinTile::CoinTile(InteractiveTileLayer& interactiveTileLayer, const std::string& name, const sf::Vector2f& pos, const int ID, const TileType type)
	:InteractiveTile(interactiveTileLayer, name, pos, ID, type),
	m_scoreValue(1)
{
	loadInCoinDetails(name);
}

void CoinTile::update(const float deltaTime)
{
	InteractiveTile::update(deltaTime);
}

void CoinTile::activate(Player & player)
{
	player.increaseScore(m_scoreValue);
	InteractiveTile::removeTile();
}

void CoinTile::loadInCoinDetails(const std::string& name)
{
	std::ifstream file(Utilities::getInteractiveTileDetails(name));
	assert(file.is_open());

	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream keyStream(line);

		if (line == "ScoreValue")
		{
			keyStream >> m_scoreValue;
		}
	}

	file.close();
}
