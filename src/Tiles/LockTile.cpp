#include "Tiles/LockTile.h"
#include "Managers/EntityManager.h"
#include "Entities/Player.h"
#include "Managers/GameManager.h"
#include "Map/WorldMap.h"
#include "Tiles/DoorTile.h"


LockTile::LockTile(InteractiveTileLayer& interactiveTileLayer, const std::string& name, const sf::Vector2f& pos, const int ID, const TileType type)
	: InteractiveTile(interactiveTileLayer, name, pos, ID, type),
	m_unlocked(false)
{}

void LockTile::activate(Player& player)
{
	if (player.isHoldingKey())
	{
		m_unlocked = true;
		DoorTile& door = *static_cast<DoorTile*>(InteractiveTile::getInteractiveTileLayer().getTile(TileType::Door));
		door.unlockDoor(*this);
		InteractiveTile::getInteractiveTileLayer().removeTile(TileType::Key);
	}
}
