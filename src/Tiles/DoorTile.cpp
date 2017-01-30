#include "Tiles/InteractiveTile.h"
#include "../../include/Tiles/DoorTile.h"
#include "Direction.h"
#include "Managers/GameManager.h"
#include "Entities/Player.h"
#include "Managers/EntityManager.h"
#include "Tiles/LockTile.h"
#include <iostream>

DoorTile::DoorTile(InteractiveTileLayer & interactiveTileLayer, const std::string & name, const sf::Vector2f & pos, const int ID, const TileType type)
	: InteractiveTile(interactiveTileLayer, name, pos, ID, type),
	m_isOpen(false)
{
}

void DoorTile::unlockDoor(const LockTile& lock)
{
	if (lock.isUnlocked())
	{
		m_isOpen = true;
		InteractiveTile::getAnimationPlayer().setCurrentAnimation("Unlocked", Direction::None);
	}
}