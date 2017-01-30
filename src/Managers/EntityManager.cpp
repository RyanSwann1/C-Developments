#include "Managers/EntityManager.h"
#include "Entities/Entity.h"
#include "Entities/EntityType.h"
#include "Entities/Player.h"
#include "Managers/GameManager.h"
#include <functional>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <sstream>
#include <fstream>

class EntityManager::EntityFactory
{
public:
	EntityFactory(GameManager& gameManager, WorldMap& worldMap, EntityManager* entityManager)
	{
		registerEntity<Player>("Player", gameManager, worldMap, entityManager, EntityType::Player);
	}

	Entity* createEntity(const std::string& name, const sf::Vector2f& pos, const int ID) const
	{
		auto cIter = m_entityFactory.find(name);
		assert(cIter != m_entityFactory.cend());
		return cIter->second(pos, ID, name);
	}

private:
	std::unordered_map<std::string, std::function<Entity*(const sf::Vector2f& pos, const int ID, const std::string& name)>> m_entityFactory;

	template <class T>
	void registerEntity(const std::string& name, GameManager& gameManager, WorldMap& worldMap, EntityManager* entityManager, const EntityType type)
	{
		assert(m_entityFactory.find(name) == m_entityFactory.cend());
		m_entityFactory.emplace(std::make_pair(name, [&gameManager, &worldMap, entityManager, type](const sf::Vector2f& pos, const int ID, const std::string& name) -> Entity*
		{
			return new T(gameManager, worldMap, *entityManager, pos, ID, name, type);
		}));
	}
};

void EntityManager::addEntity(const std::string& name, const sf::Vector2f & pos)
{
	Entity* const entity = m_entityFactory->createEntity(name, pos, m_entityCount);
	assert(entity);
	m_entities.emplace_back(entity);
	++m_entityCount;
}

EntityManager::EntityManager(GameManager & gameManager, WorldMap & worldMap)
	: m_entityFactory(new EntityFactory(gameManager, worldMap, this)),
	m_removals(),
	m_entities(),
	m_entityCount(0)
{
}

EntityManager::~EntityManager()
{
	purgeEntities();
	delete m_entityFactory;
}

Entity * EntityManager::getEntityAtPosition(const sf::Vector2f & pos, const int tileSize) const
{
	//Check to see if entity fills the same square as requested position does
	const sf::Vector2i entity1Pos(std::floor(pos.x) / tileSize, std::floor(pos.y) / tileSize);

	for (const auto &i : m_entities)
	{
		const sf::Vector2i entity2Pos(std::floor(i->getPosition().x) / tileSize, std::floor(i->getPosition().y) / tileSize);
		if (entity1Pos == entity2Pos)
		{
			return i;
		}
	}

	return nullptr;
}

Entity * EntityManager::getEntity(const EntityType type) const
{
	return nullptr;
}

//void EntityManager::addEntity(const std::string& name)
//{
//	Entity* const entity = m_entityFactory->createEntity(name);
//	if (entity)
//	{
//		entity->setID(m_entityCount);
//		m_entities.emplace_back(entity);
//		++m_entityCount;
//	}
//}

void EntityManager::update(const float deltaTime)
{
	for (auto &i : m_entities)
	{
		i->update(deltaTime);
	}

	processRemovals();
}

void EntityManager::draw(sf::RenderWindow & window)
{
	for (const auto &i : m_entities)
	{
		i->draw(window);
	}
}

void EntityManager::purgeEntities()
{
	for (auto &i : m_entities)
	{
		delete i;
		i = nullptr;
	}
	m_entities.clear();
}

void EntityManager::removeEntity(const int ID)
{
	if (std::find(m_removals.cbegin(), m_removals.cend(), ID) == m_removals.cend())
	{
		m_removals.push_back(ID);
	}
}

void EntityManager::processRemovals()
{
	for (auto iter = m_removals.begin(); iter != m_removals.end();)
	{
		if (removeActiveEntity(*iter))
		{
			iter = m_removals.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

bool EntityManager::removeActiveEntity(const int ID)
{
	auto iter = std::find_if(m_entities.begin(), m_entities.end(), [ID](Entity* const entity) {return entity->getID() == ID; });
	if (iter != m_entities.end())
	{
		delete *iter;
		*iter = nullptr;
		return true;
	}

	else 
	{
		return false;
	}
}

//void EntityManager::loadInEntityDetails(const std::string & fileName)
//{
//	std::ifstream file(fileName);
//	assert(file.is_open());
//
//	std::string line;
//	while (std::getline(file, line))
//	{
//		std::stringstream keyStream(line);
//		std::string type;
//		keyStream >> type;
//
//
//
//		if(type == )
//	}
//}
