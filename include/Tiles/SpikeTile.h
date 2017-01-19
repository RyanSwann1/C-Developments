#pragma once
#include "Tiles\InteractiveTile.h"
#include "Timer.h"
class SpikeTile :
	public InteractiveTile
{
public:
	SpikeTile(SharedContext& sharedContext, const std::string& name, const sf::Vector2f& pos, const int ID, const TileType type);
	~SpikeTile();

	void activate(Player& player) override;
private:
	Timer m_harmTimer;
};

