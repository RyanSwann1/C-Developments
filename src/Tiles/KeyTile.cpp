#include "Tiles/KeyTile.h"
#include "Managers/EntityManager.h"
#include "Entities/Player.h"
#include "Utilities.h"
#include "Map/WorldMap.h"
#include <fstream>
#include <sstream>
#include <assert.h>

KeyTile::KeyTile(InteractiveTileLayer& interactiveTileLayer, const std::string & name, const sf::Vector2f & pos, const int ID, const TileType type)
	: InteractiveTile(interactiveTileLayer, name, pos, ID, type),
	m_player(nullptr),
	m_attachToPlayer(false)
{
}

void KeyTile::update(const float deltaTime)
{
	if (m_attachToPlayer)
	{
		assert(m_player);
		InteractiveTile::moveToPosition(m_player->getPosition());
	}
}

void KeyTile::activate(Player& player)
{
	if (player.isHoldingKey())
	{
		m_attachToPlayer = true;
		m_player = &player;
	}
}
