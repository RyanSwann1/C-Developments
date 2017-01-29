#include "Tiles\BouncyTile.h"
#include "Entities\Player.h"
#include <fstream>
#include <sstream>
#include <assert.h>

BouncyTile::BouncyTile(InteractiveTileLayer & interactiveTileLayer, const std::string & name, const sf::Vector2f & pos, const int ID, const TileType type)
	: InteractiveTile(interactiveTileLayer, name, pos, ID, type)
{
}

void BouncyTile::update(const float deltaTime)
{
	InteractiveTile::getActivationTimer().update(deltaTime);
	InteractiveTile::getAnimationPlayer().update(deltaTime);

	//if (InteractiveTile::isActive())
	//{
	//	if (animation && animation->isActive())
	//	{
	//		animation->update(deltaTime);
	//		if (animation->isFinished())
	//		{
	//			animation->stop();
	//			InteractiveTile::disable();
	//		}
	//	}
	//}
}

void BouncyTile::activate(Player& player)
{
	if (!InteractiveTile::getActivationTimer().isActive())
	{
		InteractiveTile::getActivationTimer().activate();
		InteractiveTile::getAnimationPlayer().play();
	}
}
