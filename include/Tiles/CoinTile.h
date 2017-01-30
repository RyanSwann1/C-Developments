#pragma once

#include "Tiles/InteractiveTile.h"
#include "Direction.h"

class CoinTile :
	public InteractiveTile
{
public:
	CoinTile(InteractiveTileLayer& interactiveTileLayer, const std::string& name, const sf::Vector2f& pos, const int ID, const TileType type);

	int getScoreValue() const { return m_scoreValue; }
	
	void update(const float deltaTime) override;
	void activate(Player& player) override;

private:
	int m_scoreValue;

	void loadInCoinDetails(const std::string& name);
};