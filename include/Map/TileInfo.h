#pragma once

#include "Managers/TextureManager.h"
#include "Map/TileSetDetails.h"
#include "Sprite/TileSheet.h"
#include "Managers/TileSheetManager.h"
#include "Locators/TileSheetManagerLocator.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

struct TileInfo
{
	//Constructor
	TileInfo(const std::string& tileSheetName, const int tileID, const sf::Vector2i& position)
		: m_tileSheetManager(TileSheetManagerLocator::getTileSheetManager()),
		m_position(position),
		m_tileID(tileID),
		m_tileSheetName(tileSheetName)
	{
		m_sprite.setTexture(*m_tileSheetManager.getTileSheet(m_tileSheetName).getTexture());
		m_sprite.setTextureRect(m_tileSheetManager.getTileSheet(m_tileSheetName).getTileLocationByID(m_tileID));

		const int tileSize = m_tileSheetManager.getTileSheet(m_tileSheetName).getDetails().m_tileSize;
		m_sprite.setPosition(sf::Vector2f(position.x * tileSize, position.y * tileSize));
	}

	//Copy Constructor - Doesnt use constructors innards
	TileInfo(const TileInfo& orig)
		: m_position(orig.m_position),
		m_sprite(orig.m_sprite),
		m_tileID(orig.m_tileID),
		m_tileSheetName(orig.m_tileSheetName),
		m_tileSheetManager(orig.m_tileSheetManager)
	{	
		m_sprite.setTexture(*m_tileSheetManager.getTileSheet(m_tileSheetName).getTexture());
	}

	//Destructor
	~TileInfo()
	{
		m_tileSheetManager.releaseTileSheet(m_tileSheetName);
	}
	
	TileSheetManager& m_tileSheetManager;
	const sf::Vector2i m_position;
	const int m_tileID;
	const std::string m_tileSheetName;
	sf::Sprite m_sprite;
};