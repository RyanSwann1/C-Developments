#pragma once

#include <SFML/Graphics.hpp>

class Camera
{
public:

	inline const sf::Vector2f& getPosition() const { return m_position; }

private:
	sf::Vector2f m_position;
};