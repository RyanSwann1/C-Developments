#include "Map\InteractiveTileLayer.h"
#include "Tiles\BouncyTile.h"
#include "Tiles\KeyTile.h"
#include "Tiles\LadderTile.h"
#include "Tiles\LockTile.h"
#include "Tiles/DoorTile.h"
#include "Maths.h"
#include <unordered_map>
#include <functional>
#include <assert.h>
#include <algorithm>
#include <assert.h>

class InteractiveTileLayer::TileFactory
{
public:
	TileFactory(SharedContext& sharedContext)
	{
		registerTile<BouncyTile>(&sharedContext, "Bouncy");
		registerTile<KeyTile>(&sharedContext, "Key");
		registerTile<LadderTile>(&sharedContext, "Ladder");
		registerTile<LockTile>(&sharedContext, "Lock");
		registerTile<DoorTile>(&sharedContext, "Door");
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
	void registerTile(SharedContext* sharedContext, const std::string& name)
	{
		if (m_tiles.find(name) == m_tiles.cend())
		{
			m_tiles.emplace(std::make_pair(name, [sharedContext](const sf::Vector2f& pos, const int tileID, const std::string& name) -> InteractiveTile*
			{
				return new T(*sharedContext, name, pos, tileID);
			}));
		}
	}
};

InteractiveTileLayer::InteractiveTileLayer(SharedContext& sharedContext)
	: m_tileFactory(new TileFactory(sharedContext))
{

}

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

void InteractiveTileLayer::addTile(SharedContext & sharedContext, const sf::Vector2f & pos, const std::string & name, const sf::Vector2f & mapSize, const int tileID)
{
	//InteractiveTile* createTile(const std::string& id, const sf::Vector2f& pos, const int tileID, const std::string& name)
	InteractiveTile* const tile = m_tileFactory->createTile(name, pos, tileID);
	assert(tile);

	m_tileMap.emplace_back(tile);
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