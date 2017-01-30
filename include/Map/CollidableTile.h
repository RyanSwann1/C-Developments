#pragma once

#include <SFML/Graphics.hpp>

struct CollidableTile
{
	CollidableTile(const sf::Vector2i& pos)
		: m_position(pos)
	{}
	
	const sf::Vector2i m_position;
};