#pragma once

#include "Direction.h"
#include "Animations\Animation.h"
#include "Managers\TileSheetManager.h"
#include <SFML\Graphics.hpp>
#include <unordered_map>
#include <vector> 

class AnimationPlayer 
{
public:
	AnimationPlayer(const std::string& ownerName);
	~AnimationPlayer();

	//void setAnimationType(const std::string& name, const Direction dir = Direction::None);
	//void setAnimationType(const std::string& name, const Direction dir, const sf::Vector2f& pos);

	const std::string& getCurrentAnimationName() const;

	bool isAnimationFinished() const;

	void setCurrentAnimation(const std::string& name, const Direction dir = Direction::None);
	void setPosition(const sf::Vector2f& pos);
	void play();
	void stop();
	
	void update(const float deltaTime);
	void draw(sf::RenderWindow& window);

private:
	TileSheetManager& m_tileSheetManager;
	std::unordered_map<std::string, Animation> m_animations;
	Animation* m_currentAnimation;
	sf::Sprite m_sprite;
	std::string m_tileSheetName;
	void loadInAnimations(const std::string& ownerName);
};