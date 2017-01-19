#include "Tiles\BouncyTile.h"
#include "Utilities.h"
#include "Entities\Player.h"
#include <fstream>
#include <sstream>
#include <assert.h>

BouncyTile::BouncyTile(SharedContext& sharedContext, const std::string& name, const sf::Vector2f& pos, const int ID, const TileType type)
	: InteractiveTile(sharedContext, name, pos, ID, type)
{	
}

void BouncyTile::update(const float deltaTime)
{
	Animation& animation = InteractiveTile::getAnimationManager().getCurrentAnimation();
	Timer& activateTimer = InteractiveTile::getActivationTimer();

	if (activateTimer.isActive())
	{
		activateTimer.update(deltaTime);

		if (animation.isActive())
		{
			animation.update(deltaTime);
			if (animation.isFinished())
			{
				animation.stop();
			}
		}

		if (activateTimer.isExpired())
		{
			activateTimer.deactivate();
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
	if (!InteractiveTile::getActivationTimer().isActive())
	{
		Animation& animation = InteractiveTile::getAnimationManager().getCurrentAnimation();
		animation.play();
		InteractiveTile::getActivationTimer().activate();
	}
}
