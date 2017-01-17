#include "Map\WorldMap.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <assert.h>

WorldMap::WorldMap(SharedContext & sharedContext)
	: m_sharedContext(sharedContext),
	m_interactiveTileLayer(sharedContext)
{
	//loadInMapNames("MapNames.txt");
}

void WorldMap::assignTileLayer(const TileLayer & newTileLayer)
{
	if (!hasTileLayer(newTileLayer.getName()))
	{
		m_tileLayers.push_back(newTileLayer);
	}
}

void WorldMap::changeMap()
{
	clearMap();
}

void WorldMap::clearMap()
{
	m_tileLayers.clear();
	m_collidableTileLayer.clearMap();
	m_interactiveTileLayer.clearMap();
}

const bool WorldMap::hasTileLayer(const std::string& tileLayerName) const
{
	if (std::find_if(m_tileLayers.cbegin(), m_tileLayers.cend(), [tileLayerName](const auto& tileLayer) { return tileLayer.getName() == tileLayerName; }) != m_tileLayers.cend())
	{
		return true;
	}

	return false;
}

void WorldMap::update(const float deltaTime)
{
	m_interactiveTileLayer.update(deltaTime);
}

void WorldMap::draw(sf::RenderWindow & window)
{
	for (auto &i : m_tileLayers)
	{
		i.draw(window);
	}
	m_interactiveTileLayer.draw(window);
} 

//
//void WorldMap::loadTileMap()
//{
//	m_tileMap.reserve(static_cast<size_t>(m_mapSize.x * m_mapSize.y));
//
//	for (int col = 0; col < m_mapSize.y; ++col)
//	{
//		for (int row = 0; row < m_mapSize.x; ++row)
//		{
//			const int tileID = m_tileMapData[col][row]; //Get ID for tile
//			if (tileID > 0)
//			{
//				const sf::Vector2i tilePosition(row, col); //Tile Position
//				const sf::IntRect drawLocation = getTileIDDrawLocation(tileID);
//
//				Tile tile(TileInfo(m_sharedContext.m_textureManager, m_tileSetDetails, tileID, tilePosition, drawLocation));
//				//Change collision value of tile if neccessary
//				m_tileMap.emplace_back(tile);
//			}
//		}
//	}
//
//	//for (int col = 0; col < m_tileSetDetails.m_numbOfColumns; ++col)
//	//{
//	//	for (int row = 0; row < m_tileSetDetails.m_numbOfRows; ++row)
//	//	{
//	//		
//	//		
//	//	}
//	//}
//	std::cout << "Hi\n";
//}

//const sf::IntRect WorldMap::getTileIDDrawLocation(const int ID) const
//{
//	////Tile ID is out of bounds
//	//if (ID < 0 || ID > (m_tileSetDetails.m_numbOfColumns * m_tileSetDetails.m_numbOfRows))
//	//{
//	//	return;
//	//}
//
//	//Scan through every tile on tilesheet to find appropriate tile by ID
//	int col = 0, row = 0, firstGridID = 1;
//	const int endTilePos = m_tileSetDetails.m_numbOfColumns * m_tileSetDetails.m_numbOfRows;
//	for (int i = firstGridID; i < endTilePos; ++i)
//	{
//		//Appropriate tile has been found
//		if (i == ID)
//		{
//			break;
//		}
//
//		++row;
//		if (row >= m_tileSetDetails.m_numbOfRows)
//		{
//			row = 0;
//			++col;
//		}
//	}
//
//	//Draw location
//	//return sf::IntRect((m_tileSetDetails.m_spacing + (row * m_tileSetDetails.m_tileSize)), //Draw location on X Axis
//	//	(m_tileSetDetails.m_spacing + (col * m_tileSetDetails.m_tileSize)), //Draw location on Y Axis
//	//	m_tileSetDetails.m_tileSize, m_tileSetDetails.m_tileSize); //Draw Location size
//
//	//Draw location on the tile sheet
//	return sf::IntRect((m_tileSetDetails.m_margin + ((m_tileSetDetails.m_spacing + m_tileSetDetails.m_tileSize) * row)), //Draw location on X Axis
//						(m_tileSetDetails.m_margin + ((m_tileSetDetails.m_spacing + m_tileSetDetails.m_tileSize) * col)), //Draw location on Y Axis
//						m_tileSetDetails.m_tileSize, m_tileSetDetails.m_tileSize); //Draw Location size
//}
