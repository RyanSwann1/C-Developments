#include "Tiles\KeyTile.h"
#include "Managers\EntityManager.h"
#include "Entities\Player.h"
#include "Utilities.h"
#include "Map\WorldMap.h"
#include <fstream>
#include <sstream>
#include <assert.h>

KeyTile::KeyTile(SharedContext& sharedContext, const std::string& name, const sf::Vector2f& pos, const int ID)
	: InteractiveTile(sharedContext, name, pos, ID, TileType::Key),
	m_attachToPlayer(false)
{
}

void KeyTile::update(const float deltaTime)
{
	if (m_attachToPlayer)
	{
		const Entity* const player = InteractiveTile::getSharedContext().m_entityManager.getPlayer();
		assert(player);
		InteractiveTile::setPosition(player->getPosition());
	}

	//if (InteractiveTile::isActive())
	//{
	//	const Player* const player = static_cast<const Player*>(InteractiveTile::getSharedContext().m_entityManager.getPlayer());
	//	assert(player);
	//	InteractiveTile::setPosition(player->getPosition());
	//	//If player is no longer due to unlocking of door
	//	if (!player->isHoldingKey())
	//	{
	//		InteractiveTile::disable();
	//	}
	//}
}

void KeyTile::activate(Player& player)
{
	if (player.isHoldingKey())
	{
		m_attachToPlayer = true;
	}
}
