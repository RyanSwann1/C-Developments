#pragma once
#include "Entities\Entity.h"
class PowerUp :
	public Entity
{
public:
	PowerUp(SharedContext& sharedContext, const EntityType type, const sf::Vector2f& pos, const int ID, const std::string& names, const float gravityValue);
	~PowerUp();

	void update(const float deltaTime) override;

private:
	float m_value;

	void loadInPowerUpDetails();
};

