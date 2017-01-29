#pragma once

#include "Tiles/InteractiveTile.h"

class LockTile :
	public InteractiveTile
{
public:
	LockTile(InteractiveTileLayer& interactiveTileLayer, const std::string& name, const sf::Vector2f& pos, const int ID, const TileType type);
	
	void activate(Player& player) override;
	bool isUnlocked() const { return m_unlocked; }

private:
	bool m_unlocked;
};