#pragma once

#include "Tiles/InteractiveTile.h"

class SharedContext;

class LadderTile : public InteractiveTile
{
public:
	LadderTile(SharedContext& sharedContext, const std::string& name, const sf::Vector2f& pos, const int ID, const TileType type);

private:

};
