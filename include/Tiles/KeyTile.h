#pragma once

#include "Tiles/InteractiveTile.h"

class Player;
class KeyTile : public InteractiveTile
{
public:
	KeyTile(InteractiveTileLayer& interactiveTileLayer, const std::string& name, const sf::Vector2f& pos, const int ID, const TileType type);

	void update(const float deltaTime) override;
	void activate(Player& player) override;

private:
	const Player* m_player;
	bool m_attachToPlayer;
};
