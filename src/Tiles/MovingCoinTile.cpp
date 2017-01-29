#include "Tiles\MovingCoinTile.h"
#include "Entities\Player.h"
#include "Map\WorldMap.h"
#include "Utilities.h"
#include <fstream>
#include <sstream>
#include <assert.h>

MovingCoinTile::MovingCoinTile(InteractiveTileLayer& interactiveTileLayer, const std::string& name, const sf::Vector2f& pos, const int ID, const TileType type)
	: InteractiveTile(interactiveTileLayer, name, pos, ID, type),
	m_scoreValue(0)
{
	loadInCoinDetails();
	InteractiveTile::setDirection(Direction::Up);
	InteractiveTile::getMovementTimer().activate();
}

void MovingCoinTile::update(const float deltaTime)
{
	InteractiveTile::getMovementTimer().update(deltaTime);
	
	if (InteractiveTile::getMovementTimer().isActive())
	{
		InteractiveTile::moveInDirection(deltaTime);
	}
	else if (InteractiveTile::getMovementTimer().isFinished())
	{
		InteractiveTile::removeTile();
	}
}

void MovingCoinTile::activate(Player & player)
{
	player.increaseScore(m_scoreValue);
	InteractiveTile::removeTile();
}

void MovingCoinTile::loadInCoinDetails()
{
	std::ifstream file(Utilities::getInteractiveTileDetails(InteractiveTile::getName()));
	assert(file.is_open());

	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream keyStream(line);
		std::string type;
		keyStream >> type;

		if (type == "ScoreValue")
		{
			keyStream >> m_scoreValue;
		}
		else if (type == "MovementSpeed")
		{
			float speed = 0;
			keyStream >> speed;
			InteractiveTile::setMovementSpeed(speed);
		}
		else if (type == "MovementTimer")
		{
			float expirationTime = 0;
			keyStream >> expirationTime;
			InteractiveTile::getMovementTimer().setExpirationTime(expirationTime);
		}
	}

	file.close();
}