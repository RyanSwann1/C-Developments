#include "Tiles/InteractiveTile.h"
#include "Utilities.h"
#include "Entities/Player.h"
#include "Map/WorldMap.h"
#include <fstream>
#include <sstream>
#include <assert.h>

InteractiveTile::InteractiveTile(InteractiveTileLayer & interactiveTileLayer, const std::string & name, const sf::Vector2f & pos, const int ID, const TileType type)
	: m_animationPlayer(name),
	m_interactiveTileLayer(interactiveTileLayer),
	m_activationTimer(),
	m_movementTimer(),
	m_ID(ID),
	m_type(type),
	m_name(name),
	m_currentDirection(),
	m_movementSpeed(0),
	m_shape(),
	m_position(pos)
{
	m_activationTimer.setExpirationTime(1);

	m_position = sf::Vector2f(pos.x, pos.y - 16); //Minus tile size amount - Hack for Tiled
	m_animationPlayer.setPosition(m_position);
}

void InteractiveTile::draw(sf::RenderWindow & window)
{
	m_animationPlayer.draw(window);
}

void InteractiveTile::removeTile()
{
	m_interactiveTileLayer.removeTile(InteractiveTile::getID());
}

void InteractiveTile::moveInDirection(const float deltaTime)
{
	switch (m_currentDirection)
	{
		//Handle all cases of directions
	case Direction::Up :
	{
		m_position.y -= m_movementSpeed * deltaTime;
		break;
	}
	case Direction::Down :
	{
		m_position.y += m_movementSpeed * deltaTime;
		break;
	}
	case Direction::Right :
	{
		m_position.x += m_movementSpeed * deltaTime;
		break;
	}
	case Direction::Left :
	{
		m_position.x -= m_movementSpeed * deltaTime;
		break;
	}



	}

	m_animationPlayer.setPosition(m_position);
}

void InteractiveTile::moveToPosition(const sf::Vector2f & pos)
{
	m_position = pos;
	m_animationPlayer.setPosition(m_position);
}
