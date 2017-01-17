#pragma once
#include "Tiles\InteractiveTile.h"
class KeyTile : public InteractiveTile
{
public:
	KeyTile(SharedContext& sharedContext, const std::string& name, const sf::Vector2f& pos, const int ID);

	void update(const float deltaTime) override;
	void activate(Player& player) override;

private:
	bool m_attachToPlayer;
};