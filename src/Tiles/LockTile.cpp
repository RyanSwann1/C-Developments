#include "Tiles/LockTile.h"
#include "Managers\EntityManager.h"
#include "Entities\Player.h"
#include "Managers\GameManager.h"
#include "Map\WorldMap.h"
#include "Tiles\DoorTile.h"


LockTile::LockTile(SharedContext& sharedContext, const std::string& name, const sf::Vector2f& pos, const int ID)
	: InteractiveTile(sharedContext, name, pos, ID, TileType::Lock),
	m_unlocked(false)
{}

void LockTile::activate(Player& player)
{
	if (player.isHoldingKey())
	{
		m_unlocked = true;
		DoorTile& door = *static_cast<DoorTile*>(InteractiveTile::getSharedContext().m_worldMap.getInteractiveTileLayer().getTile(TileType::Door));
		door.unlockDoor(*this);
		InteractiveTile::getSharedContext().m_worldMap.getInteractiveTileLayer().removeTile(TileType::Key);
	}
}
