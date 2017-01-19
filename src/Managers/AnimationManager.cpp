#include "Managers\AnimationManager.h"
#include "Direction.h"
#include <fstream>
#include <sstream>
#include <assert.h>
#include <iostream>

AnimationManager::AnimationManager(const SharedContext& sharedContext)
	: m_sharedContext(sharedContext),
	m_currentAnimation(nullptr)
{}

void AnimationManager::update(const float deltaTime)
{
	if (m_currentAnimation)
	{
		m_currentAnimation->update(deltaTime);
	}
}

void AnimationManager::draw(sf::RenderWindow & window)
{
	if (m_currentAnimation)
	{
		m_currentAnimation->draw(window);
	}
}

void AnimationManager::loadInAnimations(const std::string & fileName)
{
	//Animations have already been loaded in
	if (!m_animations.empty())
	{
		return;
	}

	std::ifstream file(fileName);
	assert(file.is_open());
	std::string spriteSheetName;
	std::string line;
	while (std::getline(file, line))
	{
		if (line[0] == '|')
		{
			continue;
		}

		std::stringstream keyStream(line);
		std::string type;
		keyStream >> type;

		if (type == std::string("SpriteSheet"))
		{
			keyStream >> spriteSheetName;
			continue;
		}

		if (type == std::string("Animation"))
		{
			sf::Vector2i drawLocationSize;
			std::string name;
			int startRow = 0, endRow = 0, column = 0, repeatable = 0, reversible = 0;
			float frameTime;
			keyStream >> name >> startRow >> endRow >> column >> frameTime >> repeatable >> drawLocationSize.x >> drawLocationSize.y >> reversible;

			m_animations.emplace(std::make_pair(name,
				Animation(m_sharedContext.m_tileSheetManager, name, spriteSheetName, startRow, endRow, 
					column, frameTime, repeatable, sf::Vector2i(drawLocationSize.x, drawLocationSize.y), reversible)));
		}
	}
	file.close();
	
	m_currentAnimation = &m_animations.begin()->second;
	assert(m_currentAnimation);
}

//Animation * const AnimationManager::getCurrentAnimation() const
//{
//	if (m_currentAnimation)
//	{
//		return m_currentAnimation;
//	}
//	return nullptr;
//}

Animation & AnimationManager::getCurrentAnimation() const
{
	assert(m_currentAnimation);
	return *m_currentAnimation;
	// TODO: insert return statement here
}

void AnimationManager::setAnimationType(const std::string& name, const Direction dir)
{
	if (m_currentAnimation && m_currentAnimation->getName() == name)
	{
		return;
	}

	auto cIter = m_animations.find(name);
	if (cIter != m_animations.cend())
	{
		if (m_currentAnimation)
		{
			m_currentAnimation->stop();
		}
		m_currentAnimation = &cIter->second;
		m_currentAnimation->play();


		switch (dir)
		{
		case (Direction::Left):
		{
			m_currentAnimation->flip(true);
			break;
		}
		case (Direction::Right):
		{
			m_currentAnimation->flip(false);
			break;
		}
		default:
			break;
		}
	}
}

void AnimationManager::setAnimationType(const std::string & name, const Direction dir, const sf::Vector2f & pos)
{
	if (m_currentAnimation && m_currentAnimation->getName() == name)
	{
		return;
	}

	auto cIter = m_animations.find(name);
	if (cIter != m_animations.cend())
	{
		if (m_currentAnimation)
		{
			m_currentAnimation->stop();
		}
		m_currentAnimation = &cIter->second;
		m_currentAnimation->play();
		m_currentAnimation->setSpritePosition(pos);

		switch (dir)
		{
		case (Direction::Left):
		{
			m_currentAnimation->flip(true);
			break;
		}
		case (Direction::Right):
		{
			m_currentAnimation->flip(false);
			break;
		}
		default:
			break;
		}
	}
}

void AnimationManager::setPosition(const sf::Vector2f & pos)
{
	assert(m_currentAnimation);
	m_currentAnimation->setSpritePosition(pos);
}
