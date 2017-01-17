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
	inline const sf::Vector2f& getPosition() const { return m_position; }
	inline const std::string& getName() const { return m_name; }
	inline TileType getType() const { return m_type; }

	virtual void activate(Player& entity) {} //Called when player stands on same tile
	virtual void update(const float deltaTime) {}
	void draw(sf::RenderWindow& window);

protected:
	AnimationManager& getAnimationManager() { return m_animationManager; }
	SharedContext& getSharedContext() { return m_sharedContext; }

	void setPosition(const sf::Vector2f& newPos);

private:
	AnimationManager m_animationManager;
	SharedContext& m_sharedContext;
	sf::Vector2f m_position;
	const int m_ID;
	const TileType m_type;
	const std::string m_name;
	sf::RectangleShape m_shape;
	
	void loadInDetails(const std::string& fileName);
};