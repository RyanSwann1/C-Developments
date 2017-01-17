#include "..\..\include\Managers\EntityManager.h"
#include "Entities\Entity.h"
#include "Entities\Player.h"
#include <functional>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <iostream>
#include <math.h>

class EntityManager::EntityFactory
{
public:
	EntityFactory(SharedContext* sharedContext)
	{
		registerEntity<Player>("Player", sharedContext);
	}

	Entity* createEntity(const std::string& name, const sf::Vector2f& pos, const int ID) const
	{
		auto cIter = m_entityFactory.find(name);
		return cIter->second(pos, ID, name);
	}

private:
	std::unordered_map<std::string, std::function<Entity*(const sf::Vector2f& pos, const int ID, const std::string& name)>> m_entityFactory;

	template <class T>
	void registerEntity(const std::string& name, SharedContext* sharedContext)
	{
		if (m_entityFactory.find(name) == m_entityFactory.cend())
		{
			//Player::Player(SharedContext& sharedContext, const sf::Vector2f& pos, const int ID, const std::string& name)
			m_entityFactory.emplace(std::make_pair(name, [sharedContext](const sf::Vector2f& pos, const int ID, const std::string& name) -> Entity*
			{
				return new T(*sharedContext, pos, ID, name);
			}));
		}
	}
};

void EntityManager::addEntity(const std::string& name, const sf::Vector2f & pos)
{
	Entity* const entity = m_entityFactory->createEntity(name, pos, m_entityCount);
	assert(entity);
	m_entities.emplace_back(entity);
	++m_entityCount;
}

EntityManager::EntityManager(SharedContext* sharedContext)
	: m_entityFactory(new EntityFactory(sharedContext))
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

const Entity* EntityManager::getPlayer() const
{
	for (const auto &entity : m_entities)
	{
		if(entity->getType() == EntityType::Player)
		{
			return entity;
		}
	}

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