#pragma once

#include "Map/CollidableTile.h"
#include <vector>

class CollidableTileLayer
{
	friend class WorldMap;
public:

	const std::vector<CollidableTile>& getTileMap() const { return m_tileMap; }
	const CollidableTile* const getTile(const sf::Vector2i& pos) const;

	void assignMap(const std::vector<std::vector<int>>& tileData, const sf::Vector2i& mapSize);

private:
	std::vector<CollidableTile> m_tileMap;
	inline void clearMap() { m_tileMap.clear(); }
};