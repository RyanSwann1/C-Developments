#include "Tiles\InteractiveTile.h"
#include "..\..\include\Tiles\DoorTile.h"
#include "Direction.h"
#include "Managers\GameManager.h"
#include "Entities\Player.h"
#include "Managers\EntityManager.h"
#include "Tiles\LockTile.h"
#include "Managers\LevelManager.h"
#include <iostream>


DoorTile::DoorTile(SharedContext& sharedContext, const std::string& name, const sf::Vector2f& pos, const int ID, const TileType type)
	: InteractiveTile(sharedContext, name, pos, ID, type),
	m_isOpen(false)
{
}

void DoorTile::activate(Player& player)
{
	InteractiveTile::getSharedContext().m_levelManager->loadNextLevel(*this, player);
}

//void DoorTile::unlockDoor()
//{
//	if (InteractiveTile::getSharedContext().m_gameManager->isDoorUnlocked())
//	{
//		
//		m_locked = false;
//	}
//}

void DoorTile::unlockDoor(const LockTile& lock)
{
	if (lock.isUnlocked())
	{
		m_isOpen = true;
		InteractiveTile::getAnimationManager().setAnimationType("Unlocked", Direction::None, InteractiveTile::getPosition());
	}
}
