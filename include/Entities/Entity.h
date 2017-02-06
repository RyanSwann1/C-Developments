#pragma once

#include "Animations/AnimationPlayer.h"
#include "Managers/GameManager.h"
#include "Direction.h"
#include "Entities/EntityType.h"
#include "Map/WorldMap.h"
#include <SFML/Graphics.hpp>

struct CollisionElement;
class Entity
{
public:
	Entity(GameManager& gameManager, WorldMap& worldMap, EntityManager& entityManager, const sf::Vector2f& pos, const int ID, const std::string& name, const EntityType type);
	virtual ~Entity() {}
	
	const sf::FloatRect& getAABB() const { return m_AABB; }
	EntityType getType() const { return m_type; }
	const sf::Vector2f& getPosition() const { return m_position; }
	Direction getDirection() const { return m_currentDirection; }
	int getID() const { return m_ID; }
	const std::string& getName() const { return m_name; }

	virtual void handleTileCollisions(const std::vector<CollisionElement*>& collisions);
	virtual void onEntityCollision(Entity& entity) = 0;
	virtual void onInteractiveTileCollision(InteractiveTile& tile) = 0;

	void draw(sf::RenderWindow& window);
	virtual void update(const float deltaTime);

protected:
	inline const Direction getCurrentDirection() const { return m_currentDirection; }
	inline const sf::Vector2f& getVelocity() const { return m_velocity; }
	inline AnimationPlayer& getAnimationPlayer() { return m_animationPlayer; }
	inline const WorldMap& getWorldMap() const { return m_worldMap; }
	inline GameManager& getGameManager() { return m_gameManager; }

	inline void setMaxVelocity(const sf::Vector2f& maxVel) { m_maxVelocity = maxVel; }
	inline void setSpeed(const sf::Vector2f& speed) { m_speed = speed; }
	inline void setDirection(const Direction dir) { m_currentDirection = dir; }
	inline void setVelocity(const float x, const float y) { m_velocity = sf::Vector2f(x, y); }	
	inline void setOnTile(const bool i) { m_onTile = i; }
	
	inline void accelerate(const sf::Vector2f& acceleration) { m_acceleration += acceleration; }
	inline const bool isOnTile() const { return m_onTile; } //Is Entity on tile
	void moveInDirection(const Direction newDir);
	void setToStartPosition() { m_position = m_startPosition; }
	void addVelocity(const float x, const float y);
	inline void stop() { m_velocity.x = 0; }
	inline void setPosition(const sf::Vector2f& newPos) { m_position = newPos; }
	void setGravity(const float i) { m_gravity = i; }
	inline const sf::Vector2f& getStartPosition() const { return m_startPosition; }

private:
	WorldMap& m_worldMap;
	EntityManager& m_entityManager;
	GameManager& m_gameManager;
	AnimationPlayer m_animationPlayer;
	Direction m_currentDirection;
	sf::Vector2f m_velocity;
	sf::Vector2f m_maxVelocity;
	sf::Vector2f m_acceleration;
	sf::Vector2f m_speed;
	sf::Vector2f m_friction;
	sf::Vector2f m_oldPosition;
	const sf::Vector2f m_startPosition;
	sf::Vector2f m_position;
	sf::FloatRect m_AABB;
	sf::FloatRect m_drawThis;

	const EntityType m_type;
	const int m_ID;
	const std::string m_name;
	bool m_onTile; //Entity is on Tile
	float m_gravity;
	bool m_collidingOnX;
	bool m_collidingOnY;
	bool m_stationary; //Entity cannot move

	void move(const float x, const float y);
	void applyFriction();
	void applyGravity();
	void updateAABB();
	void loadInEntityDetails();
};