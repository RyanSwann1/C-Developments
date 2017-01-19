#pragma once
#include "Tiles\interactiveTile.h"

class MovingCoinTile :
	public InteractiveTile
{
public:
	MovingCoinTile(SharedContext& sharedContext, const std::string& name, const sf::Vector2f& pos, const int ID, const TileType type);

	int getScoreValue() const { return m_scoreValue; }

	void update(const float deltaTime) override;
	void activate(Player& player) override;

private:
	int m_scoreValue;

	void loadInCoinDetails();
};