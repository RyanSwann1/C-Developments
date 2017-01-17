#pragma once

#include "Sprite\Animation.h"
#include "SharedContext.h"
#include <SFML\Graphics.hpp>
#include <unordered_map>
#include <string>

enum class Direction;
class AnimationManager
{
public:
	AnimationManager(const SharedContext& sharedContext);

	AnimationManager(const AnimationManager&) = delete;
	AnimationManager& operator=(const AnimationManager&) = delete;

	Animation* const getCurrentAnimation() const { return m_currentAnimation; }

	void setAnimationType(const std::string& name, const Direction dir);
	void setAnimationType(const std::string& name, const Direction dir, const sf::Vector2f& pos);
	void setPosition(const sf::Vector2f& pos);
	void loadInAnimations(const std::string& fileName);

	void update(const float deltaTime);
	void draw(sf::RenderWindow& window);

private:
	std::unordered_map<std::string, Animation> m_animations;
	Animation* m_currentAnimation;
	SharedContext m_sharedContext;
};