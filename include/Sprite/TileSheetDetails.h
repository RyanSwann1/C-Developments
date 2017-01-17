#pragma once

#include <string>

struct TileSheetDetails
{
	TileSheetDetails(const std::string name, const int tileSize, const int rows, const int columns, const int margin, const int spacing)
		: m_name(name),
		m_tileSize(tileSize),
		m_rows(rows),
		m_columns(columns),
		m_margin(margin),
		m_spacing(spacing)
	{

	}

	const std::string m_name;
	const int m_tileSize;
	const int m_rows;
	const int m_columns;
	const int m_margin;
	const int m_spacing;
};