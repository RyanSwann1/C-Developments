#pragma once

#include "Map/Tile.h"
#include <SFML/Graphics.hpp>
#include <vector>

enum class TileType;
class InteractiveTile;
struct TileToAdd
{
	TileToAdd(const std::string& name, const sf::Vector2f& pos)
		: m_name(name),
		m_position(pos)
	{}

	const std::string m_name;
	const sf::Vector2f m_position;
};

class InteractiveTileLayer
{
	friend class WorldMap;
public:
	InteractiveTileLayer();
	~InteractiveTileLayer();

	inline std::vector<InteractiveTile*>& getTiles() { return m_tileMap; }
	void addTile(const sf::Vector2f& pos, const std::string& name) { m_tilesToAdd.push_back(TileToAdd(name, pos)); }
	InteractiveTile* getTile(const TileType type) const; //Might not need

	inline void removeTile(const int ID) { m_removals.push_back(ID); }
	void removeTile(const TileType type);

	void draw(sf::RenderWindow& window);
	void update(const float deltaTime);

private:
	class TileFactory;
	TileFactory* const m_tileFactory;
	std::vector<InteractiveTile*> m_tileMap;
	std::vector<TileToAdd> m_tilesToAdd;
	std::vector<int> m_removals;
	int m_tileCount;

	void clearMap();
	void processRemovals();
	void processTilesToAdd();
	bool removeActiveTile(const int ID);
	void addTileToMap(const TileToAdd& tileToAdd);
};