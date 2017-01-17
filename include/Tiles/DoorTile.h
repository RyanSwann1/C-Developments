#pragma once

#include "Tiles\InteractiveTile.h"

class LockTile;
class Player;
class GameManager;
class DoorTile : public InteractiveTile
{
public:
	DoorTile(SharedContext& sharedContext, const std::string& name, const sf::Vector2f& pos, const int ID);

	void unlockDoor(const LockTile& lock);
	bool isOpen() const { return m_isOpen; }

	//bool isLocked()
	void activate(Player& player) override;

private:
	bool m_isOpen;
};