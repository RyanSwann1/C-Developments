#include "Tiles/InteractiveTile.h"
#include "Utilities.h"
#include "Entities/Player.h"
#include "Map/WorldMap.h"
#include <fstream>
#include <sstream>
#include <assert.h>
//AnimationPlayer m_animationPlayer;
//WorldMap& m_worldMap;
//Timer m_activationTimer;
//Timer m_movementTimer;
//const int m_ID;
//const TileType m_type; //So that player can react in certain way to tile
//const std::string m_name;
//Direction m_currentDirection;
//float m_movementSpeed;
//sf::RectangleShape m_shape;
//sf::Vector2f m_position;

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
	//window.draw(m_shape);
	m_animationPlayer.draw(window);
}

//void InteractiveTile::loadInDetails()
//{
//	//Fine for now but should in future fail more gracefully
//	std::ifstream file(Utilities::getInteractiveTileDetails(m_name));
//	assert(file.is_open());
//
//	std::string line;
//	while (std::getline(file, line))
//	{
//		std::stringstream keyStream(line);
//		std::string type;
//		keyStream >> type;
//			
//		//Function can finish without sprite sheet being loaded in
//		if (type == "SpriteSheet")
//		{
//			std::string spriteSheetName;
//			keyStream >> spriteSheetName;
//			m_animationPlayer.loadInAnimations()
//		}
//	}
//
//	file.close();
//}

//Dont use this as a function.
//It delays the initialization of m_position and is only called once - there for can be put into the constructor instead
//If function is only called once - no pointin having it 
//void InteractiveTile::setPosition(const sf::Vector2f & pos)
//{
//	//Bit of a hack so that I can work with Tiled correctly. 
//	//Otherwise it spawns the tile in the wrong position for some reason
//	m_position = sf::Vector2f(pos.x, pos.y - m_sharedContext.m_worldMap.getMapDetails().m_tileSize);
//	m_animationManager.getCurrentAnimation().setSpritePosition(m_position);
//}

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
	//m_animationPlayer.getCurrentAnimation().setSpritePosition(m_position);
}

void InteractiveTile::moveToPosition(const sf::Vector2f & pos)
{
	m_position = pos;
	m_animationPlayer.setPosition(m_position);
}
