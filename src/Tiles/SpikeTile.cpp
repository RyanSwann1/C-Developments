#include "Tiles/SpikeTile.h"
#include "Entities/Player.h"


SpikeTile::SpikeTile(InteractiveTileLayer& interactiveTileLayer, const std::string& name, const sf::Vector2f& pos, const int ID, const TileType type)
	: InteractiveTile(interactiveTileLayer, name, pos, ID, type)
{
}

void SpikeTile::activate(Player & player)
{
	player.reduceLife();
}

void SpikeTile::update(const float deltaTime)
{
	//Implement timer when it only hurts the player for every one second or something
}
