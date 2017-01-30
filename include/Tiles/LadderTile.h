#pragma once

#include "Tiles/InteractiveTile.h"

class LadderTile : public InteractiveTile
{
public:
	//InteractiveTile(SharedContext& sharedContext, const std::string& name, const TileType type);
	LadderTile(SharedContext& sharedContext, const std::string& name, const sf::Vector2f& pos, const int ID, const TileType type);

private:

};