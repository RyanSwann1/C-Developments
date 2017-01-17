#pragma once

#include "SharedContext.h"
#include "XML\tinyxml.h"

#include <vector>
#include <string>
#include <SFML\Graphics.hpp>

struct TileSetDetails;
struct MapDetails;
class Level;
class EntityLayer;
class TileLayer;
struct LevelDetails;
class LevelParser
{
public:
	LevelParser(SharedContext& sharedContext);

	void parseLevel(const std::string& levelName);

private:
	SharedContext& m_sharedContext;

	void parseTextures(const TiXmlElement& root);
	void parseTileSet(const TiXmlElement& root);
	void parseTileMap(const TiXmlElement& root, const LevelDetails& levelDetails);
	void parseObjects(const TiXmlElement& root);
	void parseTileLayer(const TiXmlElement& root, const LevelDetails& levelDetails, const std::string& tileSheetName, const std::string& name);
	void parseInteractiveTiles(const TiXmlElement& root, const LevelDetails& levelDetails);
	void parseCollidableLayer(const TiXmlElement& root, const LevelDetails& levelDetails);
	const LevelDetails parseLevelDetails(const TiXmlElement& root) const;

	const TiXmlElement* findNode(const TiXmlElement& root, const std::string& name) const;
	const TiXmlElement* findNode(const TiXmlElement& root, const std::string& value, const std::string& name) const;
	const std::vector<std::vector<int>> decodeTileLayer(const TiXmlElement& tileLayerElement, const LevelDetails& levelDetails) const;
	const int getNumberOfTileLayers(const TiXmlElement& root) const;
	const int getNumberOfTileSets(const TiXmlElement& root) const;
};