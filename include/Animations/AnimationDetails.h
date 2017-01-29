#pragma once

#include <string>
#include <SFML\Graphics.hpp>

//Animation(TileSheetManager& tileSheetManager, const std::string& name, const std::string& tileSheetName, const int startRow,
//const int endRow, const int column, const float frameTime, const int repeatable, const sf::Vector2i& frameSize, const bool reversible);
struct AnimationDetails
{
	AnimationDetails(const std::string& name, const std::string& tileSheet, const int startRow, const int endRow, const int column,
		const float frameTime, const int repeatable, const sf::Vector2f& frameSize, const int reversible)
		: m_name(name),
		m_tileSheetName(tileSheet),
		m_startRow(startRow),
		m_endRow(endRow),
		m_column(column),
		m_frameTime(frameTime),
		m_repeatable(static_cast<bool>(repeatable)),
		m_frameSize(frameSize),
		m_reversible(static_cast<bool>(reversible))
	{}

	const std::string m_name;
	const std::string m_tileSheetName;
	const int m_startRow;
	const int m_endRow;
	const int m_column;
	const float m_frameTime;
	const bool m_repeatable;
	const sf::Vector2f m_frameSize;
	const bool m_reversible;
};