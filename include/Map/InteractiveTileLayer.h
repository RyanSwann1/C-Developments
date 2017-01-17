#pragma once

#include "Map\Tile.h"
#include "Tiles\InteractiveTile.h"
#include <SFML\Graphics.hpp>
#include <vector>

struct SharedContext;
class InteractiveTileLayer
{
	friend class WorldMap;
public:
	InteractiveTileLayer(SharedContext& sharedContext);
	~InteractiveTileLayer();

	std::vector<InteractiveTile*>& getTiles() { return m_tileMap; }
	void addTile(SharedContext& sharedContext, const sf::Vector2f& pos, const std::string& name, const sf::Vector2f& mapSize, const int tileID);
	InteractiveTile* getTile(const TileType type) const; //Might not need

		
	inline void removeTile(const int ID) { m_removals.push_back(ID); }
	void removeTile(const TileType type);

	void draw(sf::RenderWindow& window);
	void update(const float deltaTime);

private:
	class TileFactory;
	TileFactory* const m_tileFactory;
	std::vector<InteractiveTile*> m_tileMap;
	std::vector<int> m_removals;

	void clearMap();
	void processRemovals();
	bool removeActiveTile(const int ID);
};