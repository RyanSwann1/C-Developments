#include "Map\TileLayer.h"
#include "Map\WorldMap.h"
#include "Sprite\TileSheet.h"
#include "Maths.h"
#include <assert.h>
#include <iostream>

TileLayer::TileLayer(const TileMapData& tileMapData, const sf::Vector2i& mapSize, const std::string& name, const std::string& tileSheetName)
	: m_name(name),
	m_tileMap(loadTileMap(tileMapData, mapSize, tileSheetName))
{}

std::vector<TileInfo> TileLayer::loadTileMap(const TileMapData& tileMapData, const sf::Vector2i& mapSize, const std::string& tileSheetName) const
{
	std::vector<TileInfo> tileMap;
	tileMap.reserve(static_cast<size_t>(mapSize.x * mapSize.y));

	for (int col = 0; col < mapSize.y; ++col)
	{
		for (int row = 0; row < mapSize.x; ++row)
		{
			int tileID = tileMapData[col][row]; //Get ID for tile#
			if (tileID > 0)
			{
				--tileID; //Not sure why I have to do this. Reading in the TILEID as an extra +1
				const sf::Vector2i tilePosition(row, col); //Tile Position

				tileMap.emplace_back(TileInfo(tileSheetName, tileID, tilePosition));
			}
		}
	}
	return tileMap;
}

void TileLayer::draw(sf::RenderWindow & window)
{
	for (auto &i : m_tileMap)
	{
		window.draw(i.m_sprite);
	}
}