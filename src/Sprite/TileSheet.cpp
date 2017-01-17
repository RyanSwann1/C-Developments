#include "Sprite\TileSheet.h"
#include "Managers\TextureManager.h"
#include "Map\WorldMap.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <assert.h>
#include "..\..\include\Sprite\TileSheet.h"

TileSheet::TileSheet(TextureManager& textureManager, const TileSheetDetails& details)
	: m_textureManager(textureManager),
	m_details(details)
{}

const sf::Texture * const TileSheet::getTexture() const
{
	auto texture = m_textureManager.getResource(m_details.m_name);
	assert(texture);
	return texture;
}

const sf::IntRect TileSheet::getTileLocationByID(const int ID) const
{
	//Scan through every tile on tilesheet to find appropriate tile by ID
	int col = 0, row = 1;
	const int firstTileID = 0;
	const int endTileID = m_details.m_rows * m_details.m_columns;

	for (int i = firstTileID; i < endTileID; ++i)
	{
		//Appropriate tile has been found
		if (i == ID)
		{
			break;
		}

		//If tile not found, move onto the next tile in the row
		++row;

		//If reaching end of row, move onto the next
		if (row == m_details.m_rows)
		{
			row = 0;
			++col;
		}
	}

	//Get location on the tile sheet
	const int tileSize = m_details.m_tileSize;
	const int margin = m_details.m_margin;
	const int spacing = m_details.m_spacing;
	
	--row; //Not sure why I have to do this. 

	return sf::IntRect((margin + ((spacing + tileSize) * row)),
		(margin + ((spacing + tileSize) * col)),
			tileSize, tileSize);

	//return sf::IntRect((m_tileSetDetails.m_margin + ((m_tileSetDetails.m_spacing + tileSize) * row)),
	//	(m_tileSetDetails.m_margin + ((m_tileSetDetails.m_spacing + tileSize) * col)), tileSize, tileSize);
}

const sf::IntRect TileSheet::getTileLocationByPosition(const sf::IntRect & rect) const
{
	const int tileSize = m_details.m_tileSize;
	const sf::IntRect tilePos(rect.left * tileSize, rect.top * tileSize, rect.width * tileSize, rect.height * tileSize);

	return tilePos;
}