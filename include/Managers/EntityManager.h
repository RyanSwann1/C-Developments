#pragma once

#include "SharedContext.h"
#include "Entities\Entity.h"
#include <list>
#include <vector>
#include <SFML\Graphics.hpp>
#include <unordered_map>
#include <string>
#include <vector>

class Entity;
class EntityManager
{
public:
	EntityManager(SharedContext* sharedContext);
	~EntityManager();

	EntityManager(const EntityManager&) = delete;
	EntityManager& operator=(const EntityManager&) = delete;

	int getSize() const { return m_entities.size(); }
	Entity* getEntityAtPosition(const sf::Vector2f& pos, const int tileSize) const;
	Entity* getEntity(const EntityType type) const;
	const Entity* getPlayer() const;

	void addEntity(const std::string& name, const sf::Vector2f& pos);

	void update(const float deltaTime);
	void draw(sf::RenderWindow& window);

	void purgeEntities();
	void removeEntity(const int ID);

private:
	class EntityFactory;
	const EntityFactory* const m_entityFactory;
	std::list<int> m_removals;
	std::vector<Entity*> m_entities;
	int m_entityCount;

	void processRemovals();
	bool removeActiveEntity(const int ID);
};