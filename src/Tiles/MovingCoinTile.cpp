#include "Tiles\MovingCoinTile.h"
#include "Entities\Player.h"
#include "Map\WorldMap.h"
#include "Utilities.h"
#include <fstream>
#include <sstream>
#include <assert.h>

MovingCoinTile::MovingCoinTile(SharedContext& sharedContext, const std::string& name, const sf::Vector2f& pos, const int ID, const TileType type)
	: InteractiveTile(sharedContext, name, pos, ID, type),
	m_scoreValue(0)
{
	loadInCoinDetails();
	InteractiveTile::setDirection(Direction::Up);
	InteractiveTile::getMovementTimer().activate();
}

void MovingCoinTile::update(const float deltaTime)
{
	Timer& moveTimer = InteractiveTile::getMovementTimer();
	if (moveTimer.isActive())
	{
		moveTimer.update(deltaTime);
		InteractiveTile::moveInDirection(deltaTime);
		if (moveTimer.isExpired())
		{
			InteractiveTile::removeTile();
		}
	}
}

void MovingCoinTile::activate(Player & player)
{
	player.increaseScore(m_scoreValue);
	InteractiveTile::removeTile();
}

void MovingCoinTile::loadInCoinDetails()
{
	std::ifstream file(InteractiveTile::getSharedContext().m_utilities.getInteractiveTileDetails(InteractiveTile::getName()));
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