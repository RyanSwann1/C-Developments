#pragma once

#include "Map/TileInfo.h"

struct Tile
{
	Tile(const TileInfo& tileInfo)
		: m_deadly(false),
		m_warp(false),
		m_bouncy(false),
		m_tileInfo(tileInfo),
		m_climbable(false)
	{}

	const TileInfo m_tileInfo;
	bool m_deadly; //Harms entity
	bool m_warp; //Loads next level if stood on
	bool m_bouncy;
	bool m_climbable;
};
