#include "Map\CollidableTileLayer.h"
#include "Maths.h"


const CollidableTile * const CollidableTileLayer::getTile(const sf::Vector2i & pos) const
{
	for (const auto &i : m_tileMap)
	{
		if (i.m_position == pos)
		{
			return &i;
		}
	}

	return nullptr;
}

void CollidableTileLayer::assignMap(const std::vector<std::vector<int>>& tileData, const sf::Vector2i& mapSize)
{
	if (!m_tileMap.empty())
	{
		m_tileMap.clear();
	}

	for (int col = 0; col < mapSize.y; ++col)
	{
		for (int row = 0; row < mapSize.x; ++row)
		{
			const int tileID = tileData[col][row];
			if (tileID > 0)
			{
				const sf::Vector2i tilePos(row, col);
				m_tileMap.emplace_back(CollidableTile(tilePos));
			}
		}
	}
	int i = 0;
}
