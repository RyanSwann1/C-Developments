#pragma once

#include "SharedContext.h"
#include "Map/TileLayer.h"
#include "Map/InteractiveTileLayer.h"
#include "Map/CollidableTileLayer.h"
#include "MapDetails.h"
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>

class WorldMap
{
public:
	WorldMap();

	inline InteractiveTileLayer& getInteractiveTileLayer() { return m_interactiveTileLayer; }
	inline CollidableTileLayer& getCollidableTileLayer() { return m_collidableTileLayer; }
	const MapDetails& getMapDetails() const { return m_details; }

	void assignTileLayer(const TileLayer& newTileLayer);
	void setMapDetails(const MapDetails& details) { m_details = details; }

	void clearMap();
	
	inline void purgeTileLayers() { m_tileLayers.clear(); }
	const bool hasTileLayer(const std::string& tileLayerName) const;

	void update(const float deltaTime);
	void draw(sf::RenderWindow& window);

private:
	std::vector<TileLayer> m_tileLayers;
	InteractiveTileLayer m_interactiveTileLayer;
	CollidableTileLayer m_collidableTileLayer;
	MapDetails m_details;
	std::string m_currentMapName;
};