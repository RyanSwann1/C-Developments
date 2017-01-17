#pragma once

#include "Tiles/InteractiveTile.h"

class LockTile :
	public InteractiveTile
{
public:
	LockTile(SharedContext& sharedContext, const std::string& name, const sf::Vector2f& pos, const int ID);
	
	void activate(Player& player) override;
	bool isUnlocked() const { return m_unlocked; }

private:
	bool m_unlocked;
};