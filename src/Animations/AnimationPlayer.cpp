#include "Animations\AnimationPlayer.h"
#include "Managers\TileSheetManager.h"
#include "Locators\TileSheetManagerLocator.h"
#include "Direction.h"
#include "Utilities.h"
#include <assert.h>
#include <algorithm>

AnimationPlayer::AnimationPlayer(const std::string& ownerName)
	: m_tileSheetManager(TileSheetManagerLocator::getTileSheetManager()),
	m_animations(),
	m_currentAnimation(nullptr),
	m_sprite(),
	m_tileSheetName()
{
	//Really wanting to have the texture for the sprite to be assigned here
	m_sprite.setPosition(sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y - 16)); //Hack for Tiled ):
	loadInAnimations(ownerName);
}

AnimationPlayer::~AnimationPlayer()
{
	m_tileSheetManager.releaseTileSheet(m_tileSheetName);
}

void AnimationPlayer::setCurrentAnimation(const std::string & name, const Direction dir)
{
	assert(m_currentAnimation);
	if (m_currentAnimation->getName() == name)
	{
		return;
	}

	auto cIter = m_animations.find(name);
	assert(cIter != m_animations.cend());

	if (m_currentAnimation)
	{
		m_currentAnimation->stop();
	}
	m_currentAnimation = &cIter->second;
	
	switch (dir)
	{
	case Direction::Left :
	{
		m_currentAnimation->flip(true);
		break;
	}
	case Direction::Right :
	{
		m_currentAnimation->flip(false);
		break;
	}
	}
}

void AnimationPlayer::setPosition(const sf::Vector2f & pos)
{
	assert(m_currentAnimation);
	m_sprite.setPosition(m_currentAnimation->getPosition(pos));
}

void AnimationPlayer::play()
{
	assert(m_currentAnimation);
	m_currentAnimation->play();
}

void AnimationPlayer::stop()
{
	assert(m_currentAnimation);
	m_currentAnimation->stop();
}

void AnimationPlayer::loadInAnimations(const std::string& ownerName)
{
	//Get the animation details for the owner requested
	for (const std::pair<std::string, AnimationDetails> &i : Utilities::getAnimationDetails(ownerName))
	{
		m_animations.emplace(std::make_pair(i.first, i.second));
	}
	assert(&m_animations.begin()->second);
	m_currentAnimation = &m_animations.begin()->second;
	m_tileSheetName = m_currentAnimation->getTileSheetName();
	m_sprite.setTexture(*m_tileSheetManager.getTileSheet(m_tileSheetName).getTexture());
}

const std::string & AnimationPlayer::getCurrentAnimationName() const
{
	assert(m_currentAnimation);
	return m_currentAnimation->getName();
}

bool AnimationPlayer::isAnimationFinished() const
{
	assert(m_currentAnimation);
	return m_currentAnimation->isFinished();
}

void AnimationPlayer::update(const float deltaTime)
{
	assert(m_currentAnimation);
	m_currentAnimation->update(deltaTime);
}

void AnimationPlayer::draw(sf::RenderWindow & window)
{
	assert(m_currentAnimation);
	m_sprite.setTextureRect(m_currentAnimation->getDrawLocation());
	window.draw(m_sprite);
}