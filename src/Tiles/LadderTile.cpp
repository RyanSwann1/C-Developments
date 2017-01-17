#include "Tiles\LadderTile.h"

LadderTile::LadderTile(SharedContext& sharedContext, const std::string& name, const sf::Vector2f& pos, const int ID)
	: InteractiveTile(sharedContext, name, pos, ID, TileType::Ladder)
{
	
}
