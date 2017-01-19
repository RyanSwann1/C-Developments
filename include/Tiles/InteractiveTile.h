#pragma once

#include "Managers\AnimationManager.h"
#include "Map\TileInfo.h"
#include "Tiles\TileType.h"
#include "Timer.h"
#include <SFML\Graphics.hpp>

class Player;
class InteractiveTile
{
public:
	InteractiveTile(SharedContext& sharedContext, const std::string& name, const sf::Vector2f& pos, const int ID, const TileType type);
	virtual ~InteractiveTile() {}

	inline int getID() const { return m_ID; }
	const sf::Vector2f& getPosition() const { return m_position; }
	inline const std::string& getName() const { return m_name; }
	inline TileType getType() const { return m_type; }

	virtual void activate(Player& entity) {} //Called when player stands on same tile
	virtual void update(const float deltaTime) {}
	void draw(sf::RenderWindow& window);

protected:
	AnimationManager& getAnimationManager() { return m_animationManager; }
	SharedContext& getSharedContext() { return m_sharedContext; }
	Timer& getActivationTimer() { return m_activationTimer; }
	Timer& getMovementTimer() { return m_movementTimer; }

	inline void setMovementSpeed(const float i) { m_movementSpeed = i; }
	inline void setDirection(const Direction dir) { m_currentDirection = dir; }

	void removeTile();
	void moveInDirection(const float deltaTime);
	void moveToPosition(const sf::Vector2f& pos) { setPosition(pos); }

private:
	AnimationManager m_animationManager;
	SharedContext& m_sharedContext;
	Timer m_activationTimer;
	Timer m_movementTimer;
	const int m_ID;
	const TileType m_type; //So that player can react in certain way to tile
	const std::string m_name;
	Direction m_currentDirection;
	float m_movementSpeed;

	sf::RectangleShape m_shape;
	sf::Vector2f m_position;

	void loadInDetails(const std::string& fileName);
	void setPosition(const sf::Vector2f& pos);
};