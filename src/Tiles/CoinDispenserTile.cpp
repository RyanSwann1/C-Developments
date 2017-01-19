#include "Tiles\CoinDispenserTile.h"
#include "Tiles\CoinTile.h"
#include "Map\WorldMap.h"
#include "Entities\Player.h"

CoinDispenserTile::CoinDispenserTile(SharedContext& sharedContext, const std::string& name, const sf::Vector2f& pos, const int ID, const TileType type)
	: InteractiveTile(sharedContext, name, pos, ID, type),
	m_coinSpawned(false)
{

}

void CoinDispenserTile::activate(Player & player)
{
	if (!m_coinSpawned)
	{
		dispenseCoin();
		InteractiveTile::getAnimationManager().setAnimationType("CoinSpawned", Direction::None, InteractiveTile::getPosition());
		player.increaseScore(1);
		m_coinSpawned = true;
	}
}

void CoinDispenserTile::dispenseCoin()
{
	InteractiveTileLayer& tileLayer = InteractiveTile::getSharedContext().m_worldMap.getInteractiveTileLayer();
	SharedContext& sharedContext = InteractiveTile::getSharedContext();
	const sf::Vector2i& mapSize = sharedContext.m_worldMap.getMapDetails().m_mapSize;
	tileLayer.addTile(InteractiveTile::getPosition(), "MovingCoin");
}
