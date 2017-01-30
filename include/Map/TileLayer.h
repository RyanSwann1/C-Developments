#pragma once

#include "SharedContext.h"
#include "Tile.h"
#include "Sprite/TileSheetDetails.h"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

using TileMapData = std::vector<std::vector<int>>;

class TileSheetManager;
class TileLayer
{
	friend class WorldMap;
public:
	TileLayer(const TileMapData& tileMapData, const sf::Vector2i& mapSize, const std::string& name, const std::string& tileSheetName);

	const std::string& getName() const { return m_name; }
	const std::vector<TileInfo>& getTileMap() const { return m_tileMap; }

	std::vector<TileInfo> loadTileMap(const TileMapData& tileMapData, const sf::Vector2i& mapSize, const std::string& tileSheetName) const;

	void draw(sf::RenderWindow& window);

private:

	const std::vector<TileInfo> m_tileMap;
	//const std::vector<std::pair<int, TileInfo>> m_tileMap;
	const std::string m_name;
};