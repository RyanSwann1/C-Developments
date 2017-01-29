#pragma once

#include "Map\InteractiveTileLayer.h"
#include "Animations\AnimationPlayer.h"
#include "Tiles\TileType.h"
#include "Timer.h"
#include <SFML\Graphics.hpp>

class Player;
class InteractiveTile
{
public:
	InteractiveTile(InteractiveTileLayer& interactiveTileLayer, const std::string& name, const sf::Vector2f& pos, const int ID, const TileType type);
	virtual ~InteractiveTile() {}	

	inline int getID() const { return m_ID; }
	const sf::Vector2f& getPosition() const { return m_position; }
	inline const std::string& getName() const { return m_name; }
	inline TileType getType() const { return m_type; }

	virtual void activate(Player& entity) {} //Called when player stands on same tile
	virtual void update(const float deltaTime) {}
	void draw(sf::RenderWindow& window);

protected:
	AnimationPlayer& getAnimationPlayer() { return m_animationPlayer; }
	InteractiveTileLayer& getInteractiveTileLayer() { return m_interactiveTileLayer; }
	Timer& getActivationTimer() { return m_activationTimer; }
	Timer& getMovementTimer() { return m_movementTimer; }

	inline void setMovementSpeed(const float i) { m_movementSpeed = i; }
	inline void setDirection(const Direction dir) { m_currentDirection = dir; }

	void removeTile();
	void moveInDirection(const float deltaTime);
	void moveToPosition(const sf::Vector2f& pos);

private:
	AnimationPlayer m_animationPlayer;
	InteractiveTileLayer& m_interactiveTileLayer;
	Timer m_activationTimer;
	Timer m_movementTimer;
	const int m_ID;
	const TileType m_type; //So that player can react in certain way to tile
	const std::string m_name;
	Direction m_currentDirection;
	float m_movementSpeed;
	sf::RectangleShape m_shape;
	sf::Vector2f m_position;

	//void loadInDetails();
};