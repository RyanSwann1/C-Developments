#pragma once

#include <string>
#include <SFML\Graphics.hpp>

struct EntityDetails
{
	EntityDetails(const std::string& animationFileName, const float jumpTime, const float doubleJumpTime, const float hurtTime, const int damage,
		const float jumpVelocity, const int maxLives, const sf::Vector2f& speed, const sf::Vector2f& maxVelocity)
		: m_animationFileName(animationFileName),
		m_jumpTime(jumpTime),
		m_doubleJumpTime(doubleJumpTime),
		m_hurtTime(hurtTime),
		m_damage(damage),
		m_jumpVelocity(jumpVelocity),
		m_maxLives(maxLives),
		m_speed(speed),
		m_maxVelocity(maxVelocity)
	{}


	const std::string m_animationFileName;
	const float m_jumpTime;
	const float m_doubleJumpTime;
	const float m_hurtTime;
	const int m_damage;
	const float m_jumpVelocity;
	const int m_maxLives;
	const sf::Vector2f m_speed;
	const sf::Vector2f m_maxVelocity;


	//if (type == "JumpTime")
	//{
	//	keyStream >> m_jumpTime;
	//	m_jumpingTimer.setExpirationTime(m_jumpTime);
	//}
	//else if (type == "DoubleJumpTime")
	//{
	//	keyStream >> m_doubleJumpTime;
	//	m_doubleJumpTimer.setExpirationTime(m_doubleJumpTime);
	//}
	//else if (type == "HurtTime")
	//{
	//	keyStream >> m_hurtTime;
	//	m_hurtTimer.setExpirationTime(m_hurtTime);
	//}
	//else if (type == "Damage")
	//{
	//	keyStream >> m_damage;
	//}
	//else if (type == "JumpVelocity")
	//{
	//	keyStream >> m_jumpVelocity;
	//}
	//else if (type == "MaxLives")
	//{
	//	keyStream >> m_maxLives;
	//	m_lives = m_maxLives;
	//}
	//else if (type == "Animations")
	//{
	//	std::string animationFileName;
	//	keyStream >> animationFileName;
	//	Entity::getAnimationPlayer().loadInAnimations(animationFileName);
	//}
	//else if (type == "Speed")
	//{
	//	sf::Vector2f speed;
	//	keyStream >> speed.x >> speed.y;
	//	Entity::setSpeed(speed);
	//}
	//else if (type == "MaxVelocity")
	//{
	//	sf::Vector2f maxVel;
	//	keyStream >> maxVel.x >> maxVel.y;
	//	Entity::setMaxVelocity(maxVel);
	//}
};