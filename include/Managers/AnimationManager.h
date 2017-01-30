#pragma once

#include "Sprite/Animation.h"
#include "SharedContext.h"
#include "Direction.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>


class AnimationManager
{
public:
	AnimationManager(const SharedContext& sharedContext);

	AnimationManager(const AnimationManager&) = delete;
	AnimationManager& operator=(const AnimationManager&) = delete;

	Animation& getCurrentAnimation() const;

	void setAnimationType(const std::string& name, const Direction dir = Direction::None);
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