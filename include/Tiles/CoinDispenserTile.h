#pragma once

#include "Tiles/InteractiveTile.h"

class CoinDispenserTile : 
	public InteractiveTile
{
public:
	CoinDispenserTile(InteractiveTileLayer& interactiveTileLayer, const std::string& name, const sf::Vector2f& pos, const int ID, const TileType type);

	void activate(Player& player) override;

private:
	bool m_coinSpawned;
};
