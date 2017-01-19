#include "Tiles\InteractiveTile.h"
#include "Utilities.h"
#include "SharedContext.h"
#include "Entities\Player.h"
#include "Map\WorldMap.h"
#include <fstream>
#include <sstream>
#include <assert.h>

InteractiveTile::InteractiveTile(SharedContext & sharedContext, const std::string & name, const sf::Vector2f& pos, const int ID,  const TileType type)
	: m_animationManager(sharedContext),
	m_sharedContext(sharedContext),
	m_ID(ID),
	m_type(type),
	m_name(name),
	m_movementSpeed(0),
	m_currentDirection(Direction::None)
{
	loadInDetails(sharedContext.m_utilities.getInteractiveTileDetails(m_name));
	m_activationTimer.setExpirationTime(1);
	setPosition(pos);
	//FOr test
	//m_shape.setFillColor(sf::Color::Green);
	//const int tileSize = m_sharedContext.m_worldMap.getMapDetails().m_tileSize;
	//m_shape.setSize(sf::Vector2f(tileSize, tileSize));
}

void InteractiveTile::draw(sf::RenderWindow & window)
{
	//window.draw(m_shape);
	m_animationManager.draw(window);
}

void InteractiveTile::loadInDetails(const std::string & fileName)
{
	std::ifstream file(fileName);
	assert(file.is_open());

	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream keyStream(line);
		std::string type;
		keyStream >> type;

		if (type == "SpriteSheet")
		{
			std::string spriteSheetName;
			keyStream >> spriteSheetName;
			m_animationManager.loadInAnimations(spriteSheetName);
		}
	}
	file.close();
}

void InteractiveTile::setPosition(const sf::Vector2f & pos)
{
	//Bit of a hack so that I can work with Tiled correctly. 
	//Otherwise it spawns the tile in the wrong position for some reason
	m_position = sf::Vector2f(pos.x, pos.y - m_sharedContext.m_worldMap.getMapDetails().m_tileSize);
	m_animationManager.getCurrentAnimation().setSpritePosition(m_position);
}

void InteractiveTile::removeTile()
{
	InteractiveTile::getSharedContext().m_worldMap.getInteractiveTileLayer().removeTile(InteractiveTile::getID());
}

void InteractiveTile::moveInDirection(const float deltaTime)
{
	switch (m_currentDirection)
	{
	case (Direction::Up) :
	{
		m_position.y -= m_movementSpeed * deltaTime;
		break;
	}
	case (Direction::Down) :
	{
		m_position.y += m_movementSpeed * deltaTime;
		break;
	}
	default:
		break;
	}

	m_animationManager.getCurrentAnimation().setSpritePosition(m_position);
}