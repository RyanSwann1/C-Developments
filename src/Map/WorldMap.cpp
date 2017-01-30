#include "Map/WorldMap.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <assert.h>

WorldMap::WorldMap()
	: m_tileLayers(),
	m_interactiveTileLayer(),
	m_collidableTileLayer(),
	m_details(),
	m_currentMapName()
{
}

void WorldMap::assignTileLayer(const TileLayer & newTileLayer)
{
	if (!hasTileLayer(newTileLayer.getName()))
	{
		m_tileLayers.push_back(newTileLayer);
	}
}

void WorldMap::clearMap()
{
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