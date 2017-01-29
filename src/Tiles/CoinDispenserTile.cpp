#include "Tiles\CoinDispenserTile.h"
#include "Tiles\CoinTile.h"
#include "Map\WorldMap.h"
#include "Entities\Player.h"

CoinDispenserTile::CoinDispenserTile(InteractiveTileLayer& interactiveTileLayer, const std::string & name, const sf::Vector2f & pos, const int ID, const TileType type)
	: InteractiveTile(interactiveTileLayer, name, pos, ID, type),
	m_coinSpawned(false)
{
}

void CoinDispenserTile::activate(Player & player)
{
	if (!m_coinSpawned)
	{
		InteractiveTile::getInteractiveTileLayer().addTile(InteractiveTile::getPosition(), "MovingCoin");
		InteractiveTile::getAnimationPlayer().setCurrentAnimation("CoinSpawned");
		//InteractiveTile::getAnimationPlayer().setPosition(InteractiveTile::getPosition());
		player.increaseScore(1);
		m_coinSpawned = true;
	}
}