#pragma once

#include "Tiles\InteractiveTile.h"

class CoinDispenserTile : 
	public InteractiveTile
{
public:
	CoinDispenserTile(SharedContext& sharedContext, const std::string& name, const sf::Vector2f& pos, const int ID);

	void activate(Player& player) override;

private:
	bool m_coinSpawned;

	void dispenseCoin();
};