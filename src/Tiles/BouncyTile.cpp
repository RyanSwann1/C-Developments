#include "Tiles\BouncyTile.h"
#include "Utilities.h"
#include "Entities\Player.h"
#include <fstream>
#include <sstream>
#include <assert.h>

BouncyTile::BouncyTile(SharedContext& sharedContext, const std::string& name, const sf::Vector2f& pos, const int ID)
	: InteractiveTile(sharedContext, name, pos, ID, TileType::Bouncy)
{	
}

void BouncyTile::update(const float deltaTime)
{
	Animation* const animation = InteractiveTile::getAnimationManager().getCurrentAnimation();
	assert(animation);
	if (animation->isActive())
	{
		animation->update(deltaTime);
		if (animation->isFinished())
		{
			animation->stop();
		}
	}
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
	Animation* const animation = InteractiveTile::getAnimationManager().getCurrentAnimation();
	assert(animation);
	animation->play();
}
