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
	m_name(name)
{
	loadInDetails(sharedContext.m_utilities.getInteractiveTileDetails(m_name));
	setPosition(pos);
	
	//FOr test
	m_shape.setFillColor(sf::Color::Green);
	const int tileSize = m_sharedContext.m_worldMap.getMapDetails().m_tileSize;
	m_shape.setSize(sf::Vector2f(tileSize, tileSize));
	
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
}

void InteractiveTile::setPosition(const sf::Vector2f & newPos)
{
	//Bit of a hack so that I can work with Tiled correctly. 
	//Otherwise it spawns the tile in the wrong position for some reason
	sf::Vector2f p(newPos);
	p.y -= m_sharedContext.m_worldMap.getMapDetails().m_tileSize;
	assert(m_animationManager.getCurrentAnimation());
	m_animationManager.getCurrentAnimation()->setSpritePosition(p);
	m_position = p;

	//m_position = pos;
	//m_position.y -= 16;
	//m_shape.setPosition(m_position);

}
