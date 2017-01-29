#pragma once
#include "Tiles\InteractiveTile.h"

class BouncyTile : public InteractiveTile
{
public:
	BouncyTile(InteractiveTileLayer& interactiveTileLayer, const std::string& name, const sf::Vector2f& pos, const int ID, const TileType type);

	void update(const float deltaTime) override;
	void activate(Player& entity) override;
};