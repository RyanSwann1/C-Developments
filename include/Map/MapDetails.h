#pragma once

#include <SFML\Graphics.hpp>

struct MapDetails
{
	MapDetails()
		: m_tileSize(0)
	{}

	MapDetails(const int tileSize, const sf::Vector2i& mapSize)
		: m_tileSize(tileSize),
		m_mapSize(mapSize)
	{}

	int m_tileSize;
	sf::Vector2i m_mapSize;
};