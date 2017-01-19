#include "Entities\PowerUp.h"



PowerUp::PowerUp(SharedContext& sharedContext, const EntityType type, const sf::Vector2f& pos, const int ID, const std::string& name, const float gravityValue)
	: Entity(sharedContext, type, pos, ID, name)
{
}


PowerUp::~PowerUp()
{
}

void PowerUp::update(const float deltaTime)
{
	Entity::update(deltaTime);

}

void PowerUp::loadInPowerUpDetails()
{

}
