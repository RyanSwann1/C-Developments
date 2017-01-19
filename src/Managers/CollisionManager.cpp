#include "..\..\include\Managers\CollisionManager.h"
#include "SharedContext.h"
#include "Map\WorldMap.h"
#include "Map\CollidableTileLayer.h"
#include "Entities\Player.h"
#include "Map\MapDetails.h"
#include "CollisionElement.h"
#include "Managers\EntityManager.h"
#include "Map\InteractiveTileLayer.h"
#include <vector>
#include <math.h>
#include <algorithm>


const std::vector<CollisionElement*> checkForTiles(const SharedContext& sharedContext, Entity& entity);
void checkForEntities(const SharedContext& sharedContext, Entity& entity);
void checkForInteractiveTiles(const SharedContext& sharedContext, Player& entity);
void handleTileCollisions(const SharedContext& sharedContext, Entity& entity);
bool checkForCollision(const sf::Vector2f& entityPos, const sf::Vector2f& tilePos, const int tileSize);


//Passing by reference means that it'll only access the entity base member
void updateCollisions(const SharedContext & sharedContext, Entity & entity)
{
	handleTileCollisions(sharedContext, entity);
	checkForEntities(sharedContext, entity);
	
	//Only Player checks for interactive tiles
	if (entity.getType() == EntityType::Player)
	{
		checkForInteractiveTiles(sharedContext, *static_cast<Player*>(&entity));
	}
}

const std::vector<CollisionElement*> checkForTiles(const SharedContext& sharedContext, Entity& entity)
{
	const CollidableTileLayer collidableTileLayer = sharedContext.m_worldMap.getCollidableTileLayer();
	const std::vector<CollidableTile>& collisionMap = collidableTileLayer.getTileMap();
	const MapDetails mapDetails = sharedContext.m_worldMap.getMapDetails();

	//const Map& map = *m_sharedContext.m_map;
	const sf::FloatRect AABB(entity.getAABB());
	std::vector<CollisionElement*> collisions;

	const float fromX = std::floor((AABB.left - (AABB.width)) / mapDetails.m_tileSize);
	const float toX = std::floor((AABB.left + (AABB.width * 2.0f)) / mapDetails.m_tileSize);
	const float fromY = std::floor((AABB.top - (AABB.height)) / mapDetails.m_tileSize);
	const float toY = std::floor((AABB.top + (AABB.height * 2.0f)) / mapDetails.m_tileSize);

	for (int y = fromY; y < toY; ++y)
	{
		for (int x = fromX; x < toX; ++x)
		{
			const CollidableTile* const tile = collidableTileLayer.getTile(sf::Vector2i(x, y));
			if (tile)
			{
				const sf::FloatRect tileBounds(x * mapDetails.m_tileSize, y * mapDetails.m_tileSize, mapDetails.m_tileSize, mapDetails.m_tileSize);

				sf::FloatRect intersection;
				if (AABB.intersects(tileBounds, intersection))
				{
					const float area = intersection.height * intersection.width;
					collisions.emplace_back(new CollisionElement(area, intersection, tileBounds));
				}
			}
		}
	}

	return collisions;
}

void checkForEntities(const SharedContext& sharedContext, Entity& entity)
{
	const EntityManager& entityManager = sharedContext.m_entityManager;
	const int tileSize = sharedContext.m_worldMap.getMapDetails().m_tileSize;
	Entity* const entity2 = entityManager.getEntityAtPosition(entity.getPosition(), tileSize);
	if (entity2)
	{
		entity.onEntityCollision(*entity2);
		entity2->onEntityCollision(entity);
	}
}

void checkForInteractiveTiles(const SharedContext& sharedContext, Player& entity)
{
	const std::vector<InteractiveTile*>& tiles = sharedContext.m_worldMap.getInteractiveTileLayer().getTiles();
	const int tileSize = sharedContext.m_worldMap.getMapDetails().m_tileSize;

	//const sf::Vector2f entityPos = sf::Vector2f(std::floor(entity.getPosition().x / tileSize), std::floor(entity.getPosition().y / tileSize));
	for (const auto &i : tiles)
	{
		//const sf::Vector2f tilePos = sf::Vector2f(std::floor(i->getPosition().x / tileSize), std::floor(i->getPosition().y / tileSize));

		if (checkForCollision(entity.getPosition(), i->getPosition(), tileSize))
		{
			entity.onInteractiveTileCollision(*i); //Have the entity deal with the collision
		}

		//if (entityPos == tilePos)
		//{
		//	
		//}
	}
}

void handleTileCollisions(const SharedContext& sharedContext, Entity& entity)
{
	std::vector<CollisionElement*> tileCollisions = checkForTiles(sharedContext, entity);

	//Sort so collisions are in greatest area order
	std::sort(tileCollisions.begin(), tileCollisions.end(), [](CollisionElement* const col1, CollisionElement* const col2) { return col1->m_area > col2->m_area; });
	entity.handleTileCollisions(tileCollisions);

	for (auto &i : tileCollisions)
	{
		delete i;
		i = nullptr;
	}
}

bool checkForCollision(const sf::Vector2f& entityPos, const sf::Vector2f& tilePos, const int tileSize)
{
	if (entityPos.x > (tilePos.x + tileSize))
	{
		return false;
	}
	else if ((entityPos.x + tileSize) < tilePos.x)
	{
		return false;
	}
	else if (entityPos.y > (tilePos.y + tileSize))
	{
		return false;
	}
	else if (entityPos.y + tileSize < tilePos.y)
	{
		return false;
	}

	return true;
}


//#include "Managers\CollisionManager.h"
//#include "Game\Map.h"
//#include "Entities\Entity.h"
//#include "Managers\EntityManager.h"
//#include <math.h>
//#include <iostream>
//#include <SFML\Graphics.hpp>
//
//CollisionManager::CollisionManager(const SharedContext& sharedContext)
//	: m_sharedContext(sharedContext)
//{}
//
//CollisionManager::~CollisionManager()
//{}
//
//void CollisionManager::update(Entity* const entity)
//{
//	handleTileCollisions(entity);
//	handleEntityCollisions(entity);
//
//	if (!entity->m_collidingOnY)
//	{
//		entity->m_referenceTile = nullptr;
//	}
//
//	entity->resetCollisions();
//}
//
//void CollisionManager::checkEntityCollisions(Entity* const entity)
//{
//	const EntityManager& entityManager = *m_sharedContext.m_entityManager;
//	Entity* const entity2 = entityManager.getEntityAtPosition(entity->getPosition());
//	if (entity2)
//	{
//		entity->onEntityCollision(*entity2);
//		entity2->onEntityCollision(*entity);
//	}
//}
//
//void CollisionManager::checkTileCollisions(const Entity* const entity, std::vector<CollisionElement*>& collisions)
//{
//	const int tileSize = Sheet::TILE_SIZE;
//	const Map& map = *m_sharedContext.m_map;
//	const sf::FloatRect AABB(entity->getAABB());
//
//	const int fromX = std::floor((AABB.left - (AABB.width)) / tileSize);
//	const int toX = std::floor((AABB.left + (AABB.width * 2)) / tileSize);
//	const int fromY = std::floor((AABB.top - (AABB.height)) / tileSize);
//	const int toY = std::floor((AABB.top + (AABB.height * 2)) / tileSize);
//
//	for (int y = fromY; y < toY; ++y)
//	{
//		for (int x = fromX; x < toX; ++x)
//		{
//			const Tile* tile = map.getTile(x, y);
//			if (tile)
//			{
//				const sf::FloatRect tileBounds(x * tileSize, y * tileSize, tileSize, tileSize);
//
//				sf::FloatRect intersection;
//				if (AABB.intersects(tileBounds, intersection))
//				{
//					const float area = intersection.height * intersection.width;
//					collisions.push_back(new CollisionElement(area, intersection, tileBounds));
//				}
//			}
//		}
//	}
//}
//
//void CollisionManager::handleTileCollisions(Entity* const entity)
//{
//	std::vector<CollisionElement*> collisions;
//	checkTileCollisions(entity, collisions);
//	entity->resolveCollisions(collisions);
//	collisions.clear();
//}
//
//void CollisionManager::handleEntityCollisions(Entity* const entity)
//{
//	checkEntityCollisions(entity);
//}