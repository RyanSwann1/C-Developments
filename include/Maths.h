#pragma once

#include <SFML/Graphics.hpp>

namespace Maths
{
	inline const int convertCoords(const int x, const int y, const sf::Vector2i& mapSize) { return (x * mapSize.x) + y; }
}