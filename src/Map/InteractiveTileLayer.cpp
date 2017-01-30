#include "Map/InteractiveTileLayer.h"
#include "Tiles/BouncyTile.h"
#include "Tiles/KeyTile.h"
#include "Tiles/LockTile.h"
#include "Tiles/DoorTile.h"
#include "Tiles/CoinDispenserTile.h"
#include "Tiles/CoinTile.h"
#include "Tiles/MovingCoinTile.h"
#include "Maths.h"
#include <unordered_map>
#include <functional>
#include <assert.h>
#include <algorithm>
#include <assert.h>

class InteractiveTileLayer::TileFactory
{
public:
	TileFactory(InteractiveTileLayer* interactiveTileLayer)
	{
		//Keeping the factory method in mind 
		//Need to make sure that every object created has the same parameters 
		registerTile<BouncyTile>(interactiveTileLayer, "Bouncy", TileType::Bouncy);
		registerTile<KeyTile>(interactiveTileLayer, "Key", TileType::Key);
		registerTile<LockTile>(interactiveTileLayer, "Lock", TileType::Lock);
		registerTile<DoorTile>(interactiveTileLayer, "Door", TileType::Door);
		registerTile<CoinDispenserTile>(interactiveTileLayer, "CoinDispenser", TileType::CoinDispenser);
		registerTile<CoinTile>(interactiveTileLayer, "Coin", TileType::Coin);
		registerTile<MovingCoinTile>(interactiveTileLayer, "MovingCoin", TileType::Coin);
		registerTile<InteractiveTile>(interactiveTileLayer, "Ladder", TileType::Ladder);
	}

	//SharedContext & sharedContext, const sf::Vector2f & pos, const std::string & name, const sf::Vector2f & mapSize, const int tileID
	InteractiveTile* createTile(const std::string& name, const sf::Vector2f& pos, const int tileID) const
	{
		auto cIter = m_tiles.find(name);
		assert(cIter != m_tiles.cend());
		return cIter->second(pos, tileID, name);
	}

private:
	std::unordered_map<std::string, std::function<InteractiveTile*(const sf::Vector2f& pos, const int tileID, const std::string& name)>> m_tiles;

	template <class T>
	void registerTile(InteractiveTileLayer* interactiveTileLayer, const std::string& name, const TileType type)
	{
		if (m_tiles.find(name) == m_tiles.cend())
		{
			m_tiles.emplace(std::make_pair(name, [interactiveTileLayer, type](const sf::Vector2f& pos, const int tileID, const std::string& name) -> InteractiveTile*
			{
				return new T(*interactiveTileLayer, name, pos, tileID, type);
			}));
		}
	}
};

InteractiveTileLayer::InteractiveTileLayer()
	: m_tileFactory(new TileFactory(this)),
	m_tileMap(),
	m_tilesToAdd(),
	m_removals(),
	m_tileCount(0)
{}

InteractiveTileLayer::~InteractiveTileLayer()
{
	delete m_tileFactory;
	clearMap();
}

void InteractiveTileLayer::removeTile(const TileType type)
{
	for (const auto &tile : m_tileMap)
	{
		if (tile->getType() == type)
		{
			m_removals.push_back(tile->getID());
		}
	}
}

void InteractiveTileLayer::draw(sf::RenderWindow & window)
{
	for (const auto &i : m_tileMap)
	{
		i->draw(window);
	}
}

void InteractiveTileLayer::update(const float deltaTime)
{
	for (auto &i : m_tileMap)
	{
		i->update(deltaTime);
	}

	processRemovals();
	processTilesToAdd();
}

void InteractiveTileLayer::clearMap()
{
	for (auto &i : m_tileMap)
	{
		delete i;
		i = nullptr;
	}

	m_tileMap.clear();
}

void InteractiveTileLayer::processRemovals()
{
	for (auto iter = m_removals.begin(); iter != m_removals.end();)
	{
		if (removeActiveTile(*iter))
		{
			iter = m_removals.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void InteractiveTileLayer::processTilesToAdd()
{
	if (m_tilesToAdd.empty())
	{
		return;
	}

	for (const auto &i : m_tilesToAdd)
	{
		addTileToMap(i);
	}

	m_tilesToAdd.clear();
}

bool InteractiveTileLayer::removeActiveTile(const int ID)
{
	auto iter = std::find_if(m_tileMap.begin(), m_tileMap.end(), [ID](InteractiveTile* const tile) {return tile->getID() == ID; });
	if (iter != m_tileMap.cend())
	{
		delete *iter;
		*iter = nullptr;
		m_tileMap.erase(iter);
		return true;
	}

	return false;
}

void InteractiveTileLayer::addTileToMap(const TileToAdd & tileToAdd)
{
	//InteractiveTile* createTile(const std::string& id, const sf::Vector2f& pos, const int tileID, const std::string& name)
	InteractiveTile* const tile = m_tileFactory->createTile(tileToAdd.m_name, tileToAdd.m_position, m_tileCount);
	m_tileMap.emplace_back(tile);
	++m_tileCount;
}

InteractiveTile * InteractiveTileLayer::getTile(const TileType type) const
{
	for (const auto &i : m_tileMap)
	{
		if (i->getType() == type)
		{
			return i;
		}
	}

	return nullptr;
}

//InteractiveTile* const InteractiveTileLayer::getTile(const TileType type)
//{
//	for (auto &tile : m_tileMap)
//	{
//		if (tile->getType() == type)
//		{
//			return tile;
//		}
//	}
//
//	return nullptr;
//}