#include "Parser/LevelParser.h"
#include "Map/TileLayer.h"
#include "Entities/Entity.h"
#include "zlib.h"
#include "XML/tinystr.h"
#include "Map/WorldMap.h"
#include "Base64.h"
#include "Managers/TextureManager.h"
#include "Locators/TextureManagerLocator.h"
#include "Map/MapDetails.h"
#include "Managers/EntityManager.h"
#include "Managers/TileSheetManager.h"
#include "Locators/TileSheetManagerLocator.h"
#include "Map/InteractiveTileLayer.h"
#include "Sprite/TileSheetDetails.h"
#include <assert.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <SFML/Graphics.hpp>
#include "XML/tinyxml.h"

struct LevelDetails
{
	LevelDetails(const int tileSize, const sf::Vector2i& mapSize)
		: m_tileSize(tileSize),
		m_mapSize(mapSize)
	{}

	const int m_tileSize;
	const sf::Vector2i m_mapSize;
};

void parseTextures(const TiXmlElement & root);
void parseTileSet(const TiXmlElement & root);
void parseTileMap(WorldMap& worldMap, const TiXmlElement & root, const LevelDetails & levelDetails);
void parseObjects(EntityManager& entityManager, const TiXmlElement & root);
void parseTileLayer(WorldMap& worldMap, const TiXmlElement & tileLayerElement, const LevelDetails& levelDetails, const std::string& tileSheetName, const std::string& name);
void parseInteractiveTiles(WorldMap& worldMap, const TiXmlElement & root, const LevelDetails & levelDetails);
void parseCollidableLayer(WorldMap& worldMap, const TiXmlElement & root, const LevelDetails& levelDetails);
const LevelDetails parseLevelDetails(const TiXmlElement& root);

const TiXmlElement* findNode(const TiXmlElement& root, const std::string& name);
const TiXmlElement* findNode(const TiXmlElement& root, const std::string& value, const std::string& name);
const std::vector<std::vector<int>> decodeTileLayer(const TiXmlElement& tileLayerElement, const LevelDetails& levelDetails);
const int getNumberOfTileLayers(const TiXmlElement& root);
const int getNumberOfTileSets(const TiXmlElement& root);

void parseLevel(GameManager& gameManager, WorldMap& worldMap, EntityManager& entityManager, const std::string & levelName)
{
	//Load XML file
	TiXmlDocument levelDocument;
	assert(levelDocument.LoadFile(levelName.c_str()));

	//Get root node of the level object
	const TiXmlElement& rootNode = *levelDocument.RootElement();

	//make for loop
	//Count how many tile layers  there are on each map
	//Load each tile layer into the world map

	//Create level
	const LevelDetails levelDetails = parseLevelDetails(rootNode);
	worldMap.setMapDetails(MapDetails(levelDetails.m_tileSize, sf::Vector2i(levelDetails.m_mapSize)));
	parseTileSet(rootNode);
	parseTileMap(worldMap, rootNode, levelDetails);
	parseCollidableLayer(worldMap, rootNode, levelDetails);
	parseInteractiveTiles(worldMap, rootNode, levelDetails);

	//Load in objects
	parseObjects(entityManager, rootNode);
	
	//m_sharedContext.m_entityManager.addEntity("Player", );

	//Fix when multiple tile layers are being loaded into the program at once - Most probably the same ones 
}

//Use for parsing object textures - not possibly needed will have to see further into development
void parseTextures(const TiXmlElement & root)
{
	for (const TiXmlElement* e = root.FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == "property")
		{
			TextureManagerLocator::getTextureManager().registerFilePath(e->Attribute("name"), e->Attribute("value"));
		}
	}
}

void parseObjects(EntityManager& entityManager, const TiXmlElement & root)
{
	const TiXmlElement& objectRoot = *findNode(root, "objectgroup", "Object Layer");
	for (const TiXmlElement* e = objectRoot.FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		const std::string name(e->Attribute("name"));
		int xPos = 0, yPos = 0;
		e->Attribute("x", &xPos);
		e->Attribute("y", &yPos);

		entityManager.addEntity(name, sf::Vector2f(xPos, yPos));
	}
}

void parseTileLayer(WorldMap& worldMap, const TiXmlElement & tileLayerElement, const LevelDetails& levelDetails, const std::string& tileSheetName, const std::string& name)
{
	const std::vector<std::vector<int>> tileData = decodeTileLayer(tileLayerElement, levelDetails);
	
	TileLayer tileLayer(tileData, levelDetails.m_mapSize, name, tileSheetName);
	worldMap.assignTileLayer(tileLayer);
}

void parseInteractiveTiles(WorldMap& worldMap, const TiXmlElement & root, const LevelDetails & levelDetails)
{
	const TiXmlElement& objectRoot = *findNode(root, "objectgroup", "Interactive Tile Layer");
	for (const TiXmlElement* e = objectRoot.FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		assert(e->Attribute("name"));
		const std::string name(e->Attribute("name"));
		int xPos = 0, yPos = 0;
		e->Attribute("x", &xPos);
		e->Attribute("y", &yPos);

		worldMap.getInteractiveTileLayer().addTile(sf::Vector2f(xPos, yPos), name);
	}
}

void parseCollidableLayer(WorldMap& worldMap, const TiXmlElement & root, const LevelDetails& levelDetails)
{
	for (const TiXmlElement* e = root.FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("layer") && e->Attribute("name") == std::string("Collidable Layer"))
		{
			const std::string layerName = e->Attribute("name");
			const std::vector<std::vector<int>> tileData = decodeTileLayer(*e, levelDetails);

			worldMap.getCollidableTileLayer().assignMap(tileData, levelDetails.m_mapSize);
		}
	}
}

const LevelDetails parseLevelDetails(const TiXmlElement & root)
{
	int width = 0, height = 0, tileSize = 0;
	root.Attribute("width", &width);
	root.Attribute("height", &height);
	root.Attribute("tilewidth", &tileSize);
	
	return LevelDetails(tileSize, sf::Vector2i(width, height));
}

const TiXmlElement * findNode(const TiXmlElement& root, const std::string & name)
{
	for (const TiXmlElement* e = root.FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == name)
		{
			return e;
		}
	}
	return nullptr;
}

const TiXmlElement *findNode(const TiXmlElement & root, const std::string & value, const std::string & name)
{
	for (const TiXmlElement* e = root.FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == value && e->Attribute("name") == name)
		{
			return e;
		}
	}

	return nullptr;
}

const std::vector<std::vector<int>> decodeTileLayer(const TiXmlElement & tileLayerElement, const LevelDetails & levelDetails)
{
	std::vector<std::vector<int>> tileData;

	std::string decodedIDs; //Base64 decoded information
	const TiXmlElement* dataNode = nullptr; //Store our node once we find it
	for (const TiXmlElement* e = tileLayerElement.FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("data"))
		{
			dataNode = e;
		}
	}

	Base64 base64;
	//Get the text from within the node and use base64 to decode it
	for (const TiXmlNode* e = dataNode->FirstChild(); e != nullptr; e = e->NextSibling())
	{
		const TiXmlText* text = e->ToText();
		std::string t = text->Value();
		decodedIDs = base64.base64_decode(t);
	}

	uLongf sizeOfIDs = levelDetails.m_mapSize.x * levelDetails.m_mapSize.y * sizeof(int);
	std::vector<int> ids(levelDetails.m_mapSize.x * levelDetails.m_mapSize.y);

	uncompress((Bytef*)&ids[0], &sizeOfIDs, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());

	std::vector<int> layerRow(levelDetails.m_mapSize.x);
	for (int i = 0; i < levelDetails.m_mapSize.y; ++i)
	{
		tileData.push_back(layerRow);
	}

	for (int rows = 0; rows < levelDetails.m_mapSize.y; ++rows)
	{
		for (int cols = 0; cols < levelDetails.m_mapSize.x; ++cols)
		{
			tileData[rows][cols] = ids[rows * levelDetails.m_mapSize.x + cols];
		}
	}

	return tileData;
}

const int getNumberOfTileLayers(const TiXmlElement & root)
{
	int tileLayerCount = 0;
	for (const TiXmlElement* e = root.FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("layer"))
		{
			++tileLayerCount;
		}
	}
	return tileLayerCount;
}

const int getNumberOfTileSets(const TiXmlElement & root)
{
	int tileSetCount = 0;
	const TiXmlElement& tileSetNode = *findNode(root, "tileset");
	for (const TiXmlElement* e = &tileSetNode; e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset") && e->Attribute("name") != std::string("Collidable"))
		{
			++tileSetCount;
		}
	}
	return tileSetCount;
}

void parseTileSet(const TiXmlElement & root)
{
	bool continueSearching = true;
	const TiXmlElement* tileSetNode = findNode(root, "tileset");
	while (continueSearching)
	{
		if (tileSetNode->Value() == std::string("tileset") && tileSetNode->Attribute("name") != std::string("Collidable")) 
		{
			//Register the tile set texture
			const TiXmlElement* const imgRoot = tileSetNode->FirstChildElement("image");
			if (imgRoot)
			{
				const std::string tileSetFileName = tileSetNode->Attribute("name");
				const std::string tileSetSource = imgRoot->Attribute("source");
				TextureManagerLocator::getTextureManager().registerFilePath(tileSetFileName, imgRoot->Attribute("source"));
			}

			sf::Vector2i pos, tileSetSize;
			int spacing = 0, margin = 0, firstGridID = 0, tileSize = 0;
			//Load in values
			tileSetNode->FirstChildElement()->Attribute("width", &tileSetSize.x);
			tileSetNode->FirstChildElement()->Attribute("height", &tileSetSize.y);
			tileSetNode->Attribute("firstgid", &firstGridID);
			tileSetNode->Attribute("tilewidth", &tileSize);
			tileSetNode->Attribute("spacing", &spacing);
			tileSetNode->Attribute("margin", &margin);
			const std::string name = tileSetNode->Attribute("name");
			const int numbOfRows = tileSetSize.x / (tileSize + spacing);
			const int numbOfColumns = tileSetSize.y / (tileSize + spacing);

			const TileSheetDetails tileSheetDetails(name, tileSize, numbOfRows, numbOfColumns, margin, spacing);
			TileSheetManagerLocator::getTileSheetManager().addTileSheet(tileSheetDetails);
		}
		
		//Change to the next tileset
		if (tileSetNode->NextSiblingElement())
		{
			tileSetNode = tileSetNode->NextSiblingElement();
		}
		else
		{
			continueSearching = false;
		}
	}
}

void parseTileMap(WorldMap& worldMap, const TiXmlElement & root, const LevelDetails & levelDetails)
{
	const int tileLayerCount = getNumberOfTileLayers(root);
	const TiXmlElement* tileLayerNode = findNode(root, "layer"); //Get the first layer node

	for (int i = 1; i <= tileLayerCount; ++i)
	{
		//If node in question is a layer 
		if (tileLayerNode->Value() == std::string("layer") &&
			tileLayerNode->Attribute("name") == std::string("Tile Layer " + std::to_string(i)))
		{
			const std::string tileLayerName = tileLayerNode->Attribute("name");

			if (tileLayerNode->FirstChildElement()->Value() == std::string("data") ||
				tileLayerNode->FirstChildElement()->NextSiblingElement() != 0 && tileLayerNode->FirstChildElement()->NextSiblingElement()->Value() == std::string("data"))
			{
				if (!worldMap.hasTileLayer(tileLayerName))
				{	
					//Find correct tilesheet that corresponds with this tile layer
					if (tileLayerNode->FirstChildElement()->Value() == std::string("properties"))
					{
						const TiXmlElement& tileLayerProperty = *tileLayerNode->FirstChildElement()->FirstChildElement();
						const std::string tileSheetName = tileLayerProperty.Attribute("value");
						const TileSheet& tileSheet = TileSheetManagerLocator::getTileSheetManager().getTileSheet(tileSheetName);

						parseTileLayer(worldMap, *tileLayerNode, levelDetails, tileSheet.getDetails().m_name, tileLayerName);
					}
				}
			}
		}
		if (tileLayerNode->NextSiblingElement())
		{
			//Go to the next layer
			tileLayerNode = tileLayerNode->NextSiblingElement(); 
		}		
	}
}
