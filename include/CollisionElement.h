#pragma once

#include <SFML\Graphics.hpp>

struct CollisionElement
{
	CollisionElement(const float area, const sf::FloatRect& intersection, const sf::FloatRect& collisionBox)
		: m_area(area),
		m_intersection(intersection),
		m_collisionBox(collisionBox)
	{}

	const float m_area;
	const sf::FloatRect m_intersection;
	const sf::FloatRect m_collisionBox;
};
