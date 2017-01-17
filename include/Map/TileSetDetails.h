#pragma once

#include <string>
#include <SFML\Graphics.hpp>

struct TileSetDetails
{
	TileSetDetails()
	{}

	TileSetDetails(const std::string& name, const sf::Vector2i& tileSetSize, const int tileSize, const int firstGridID,
		const int margin, const int spacing, const int numbOfColumns, const int numbOfRows)
		: m_name(name),
		m_tileSetSize(tileSetSize),
		m_tileSize(tileSize),
		m_firstGridID(firstGridID),
		m_margin(margin),
		m_spacing(spacing),
		m_numbOfColumns(numbOfColumns),
		m_numbOfRows(numbOfRows)
	{}

	std::string m_name;
	sf::Vector2i m_tileSetSize;
	int m_tileSize;
	int m_firstGridID;
	int m_margin;
	int m_spacing;
	int m_numbOfColumns;
	int m_numbOfRows;
};