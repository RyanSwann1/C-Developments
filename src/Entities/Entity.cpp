#include "Entities\Entity.h"
#include "Map\WorldMap.h"
#include "Utilities.h"
#include "CollisionElement.h"

#include <math.h>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <iostream>

Entity::Entity(SharedContext & sharedContext, const EntityType type, const sf::Vector2f& pos, const int ID, const std::string& name)
	: m_sharedContext(sharedContext),
	m_animationManager(sharedContext),
	m_startPosition(pos),
	m_position(m_startPosition),
	m_onTile(false),
	m_gravity(0),
	m_ID(ID),
	m_collidingOnX(false),
	m_collidingOnY(false),
	m_type(type),
	m_name(name)
{
	m_maxVelocity = sf::Vector2f(60, 10000);
	m_friction.x = 0.05f;
	m_gravity = 0.4f;

	const int tileSize = m_sharedContext.m_worldMap.getMapDetails().m_tileSize;
	m_AABB.width = tileSize;
	m_AABB.height = tileSize;
}

void Entity::handleTileCollisions(const std::vector<CollisionElement*>& collisions)
{
	for (const auto &i : collisions)
	{
		const sf::FloatRect AABB(getAABB());
		//Make sure that entity is still colliding with the collision box in question
		if (!AABB.intersects(i->m_collisionBox))
		{
			continue;
		}

		const sf::FloatRect collisionBox(i->m_collisionBox);
		const float xDifference = (AABB.left + (AABB.width / 2.0f)) - (collisionBox.left + (collisionBox.width / 2.0f));
		const float yDifference = (AABB.top + (AABB.height / 2.0f)) - (collisionBox.top + (collisionBox.height / 2.0f));
		float resolve = 0;

		const sf::FloatRect intersection(i->m_intersection);
		if (std::abs(xDifference) > std::abs(yDifference))
		{
			if (xDifference > 0) {
				resolve = intersection.width;
			}
			else {
				resolve = -intersection.width;
			}
			move(resolve, 0);
			m_velocity.x = 0;
			m_collidingOnX = true;
		}
		else
		{
			if (yDifference > 0) {
				resolve = intersection.height;
			}
			else {
				resolve = -intersection.height;
			}
			move(0, resolve);
			m_velocity.y = 0;
			m_collidingOnY = true;
		}

		//Assign the reference tile for the entity
		//if (m_collidingOnY)
		//{
		//	//m_collisionBoxes.push_back(CollisionBox(sf::Vector2f(collisionBox.left, collisionBox.top)));
		//	//const Map& map = *m_sharedContext.m_map;
		//	const CollidableTileLayer& tileLayer = m_sharedContext.m_worldMap.getCollidableTileLayer();
		//	const MapDetails mapDetails = m_sharedContext.m_worldMap.getMapDetails();
		//	const CollidableTile* const tile = tileLayer.getTile(i.m_collisionBox.left / mapDetails.m_tileSize, i.m_collisionBox.top / mapDetails.m_tileSize, mapDetails.m_mapSize);
		//	if (tile)
		//	{
		//		//Just use collidable tile as interactive tile
		//		//Mark as collidable within the tiled application
		//		m_referenceTile = tile;
		//	}
		//}
	}
	//(m_collidingOnY ? m_onTile = true : m_onTile = false);
	if (m_collidingOnY)
	{
		m_onTile = true;
	}
	else
	{
		m_onTile = false;
	}
}

void Entity::draw(sf::RenderWindow & window)
{
	/*sf::RectangleShape shape(sf::Vector2f(16, 16));
	shape.setPosition(m_position);
	shape.setFillColor(sf::Color::Green);
	window.draw(shape);*/
	m_animationManager.draw(window);
}

void Entity::update(const float deltaTime)
{
	applyGravity();
	applyFriction();

	const sf::Vector2f deltaPos = m_velocity * deltaTime;
	move(deltaPos.x, deltaPos.y);

	//if (m_onTile)
	//{
	//	setVelocity(getVelocity().x, 0);
	//}

	m_collidingOnX = false;
	m_collidingOnY = false;

	updateAABB();
	m_animationManager.update(deltaTime);
	m_animationManager.setPosition(m_position);
	updateCollisions(m_sharedContext, *this);
}

void Entity::moveInDirection(const Direction newDir)
{
	if (m_currentDirection != newDir)
	{
		m_currentDirection = newDir;
	}

	switch (m_currentDirection)
	{
	case (Direction::Right):
	{
		setVelocity(m_speed.x, m_velocity.y);
		break;
	}
	case (Direction::Left):
	{
		setVelocity(-m_speed.x, m_velocity.y);
		break;
	}
	case (Direction::Up):
	{
		setVelocity(0, -m_speed.y);
		break;
	}
	case (Direction::Down) :
	{
		setVelocity(0, m_speed.y);
		break;
	}
	default:
		break;
	}
}

void Entity::addVelocity(const float x, const float y)
{
	m_velocity += sf::Vector2f(x, y);

	if (std::abs(m_velocity.x) > m_maxVelocity.x)
	{
		if (m_velocity.x > 0)
		{
			m_velocity.x = m_maxVelocity.x;
		}
		else
		{
			m_velocity.x = -m_maxVelocity.x;
		}
	}

	if (std::abs(m_velocity.y) > m_maxVelocity.y)
	{
		if (m_velocity.y > 0)
		{
			m_velocity.y = m_maxVelocity.y;
		}
		else
		{
			m_velocity.y = -m_maxVelocity.y;
		}
	}
}

void Entity::move(const float x, const float y)
{
	m_oldPosition = m_position;
	m_position += sf::Vector2f(x, y);

	//Keep position within bounds of map
	//const sf::Vector2i& mapSize = m_sharedContext.m_worldMap.getMapSize();
	//if (m_position.x < 0)
	//{
	//	m_position.x = 0;
	//}
	//else if (m_position.x > mapSize.x)
	//{
	//	m_position.x = mapSize.x;
	//}
}

void Entity::applyFriction()
{
	if (std::abs(m_velocity.x) > 0.0f)
	{
		if (m_velocity.x > 0.0f)
		{
			m_velocity.x -= m_friction.x;
		}
		else
		{
			m_velocity.x += m_friction.x;
		}
	}
}

//void Entity::setVelocity(const float x, const float y)
//{
//	if (std::abs(m_velocity.x) > m_maxVelocity.x || std::abs(m_velocity.y) > m_maxVelocity.y)
//	{
//		return;
//	}
//
//	if (std::abs(x) > 0)
//	{
//		m_velocity.x = x;
//		//if (x > 0)
//		//{
//		//	
//		//}
//		//else
//		//{
//		//	m_velocity.x = -x;
//		//}
//	}
//	
//	if (std::abs(y) > 0)
//	{
//		if (y > 0)
//		{
//			m_velocity.y = y;
//		}
//		else
//		{
//			m_velocity.y = -y;
//		}
//	}
//}

void Entity::applyGravity()
{
	if (!m_onTile)
	{
		m_velocity.y += m_gravity;
	}
}

void Entity::updateAABB()
{
	m_AABB.left = m_position.x;
	m_AABB.top = m_position.y;
}