#pragma once

#include "Tiles/InteractiveTile.h"

class LockTile;
class DoorTile : public InteractiveTile
{
public:
	DoorTile(InteractiveTileLayer& interactiveTileLayer, const std::string& name, const sf::Vector2f& pos, const int ID, const TileType type);

	void unlockDoor(const LockTile& lock);
	bool isOpen() const { return m_isOpen; }

private:
	bool m_isOpen;
};
