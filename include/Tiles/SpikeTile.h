#pragma once
#include "Tiles\InteractiveTile.h"
#include "Timer.h"
class SpikeTile :
	public InteractiveTile
{
public:
	SpikeTile(InteractiveTileLayer& interactiveTileLayer, const std::string& name, const sf::Vector2f& pos, const int ID, const TileType type);

	void activate(Player& player) override;
	void update(const float deltaTime) override;

private:
	Timer m_harmTimer;
};

