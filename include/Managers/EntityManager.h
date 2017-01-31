#pragma once

#include <list>
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

enum class EntityType;
class GameManager;
class WorldMap;
class Entity;
class EntityManager
{
public:
	EntityManager(GameManager& gameManager, WorldMap& worldMap);
	~EntityManager();

	EntityManager(const EntityManager&) = delete;
	EntityManager& operator=(const EntityManager&) = delete;

	int getSize() const { return m_entities.size(); }
	Entity* getEntityAtPosition(const sf::Vector2f& pos, const int tileSize) const;
	Entity* getEntity(const EntityType type) const;

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
