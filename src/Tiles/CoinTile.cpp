#include "Tiles\CoinTile.h"
#include "Entities\Player.h"
#include "Map\WorldMap.h"
#include "Utilities.h"
#include <fstream>
#include <sstream>
#include <assert.h>

CoinTile::CoinTile(SharedContext& sharedContext, const std::string& name, const sf::Vector2f& pos, const int ID, const TileType type)
	:InteractiveTile(sharedContext, name, pos, ID, type),
	m_scoreValue(1)
{
	loadInCoinDetails();
}

void CoinTile::update(const float deltaTime)
{
	InteractiveTile::update(deltaTime);

	//if (!m_playerScoreIncreased && m_movementTimer.isActive())
	//{
	//	move(deltaTime);
	//	//Destroy this when timer is expired
	//	if (m_movementTimer.isExpired())
	//	{
	//		InteractiveTileLayer& tileLayer = InteractiveTile::getSharedContext().m_worldMap.getInteractiveTileLayer();
	//		tileLayer.removeTile(InteractiveTile::getID());
	//	}
	//}
	//else if (m_playerScoreIncreased)
	//{
	//	
	//}
}

void CoinTile::activate(Player & player)
{
	player.increaseScore(m_scoreValue);
	InteractiveTile::removeTile();
}

void CoinTile::loadInCoinDetails()
{
	std::ifstream file(InteractiveTile::getSharedContext().m_utilities.getInteractiveTileDetails(InteractiveTile::getName()));
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