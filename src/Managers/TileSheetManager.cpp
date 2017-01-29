#include "Managers\TileSheetManager.h"
#include "Locators\TileSheetManagerLocator.h"
#include <assert.h>

TileSheetManager::TileSheetManager()
	: m_tileSheets()
{
	TileSheetManagerLocator::provide(*this);
}



TileSheet& TileSheetManager::getTileSheet(const std::string& name)
{
	auto cIter = m_tileSheets.find(name);
	assert(cIter != m_tileSheets.cend());
	return cIter->second;
}

void TileSheetManager::addTileSheet(const TileSheetDetails& tileSheetDetails)
{
	//assert(m_tileSheets.emplace(std::make_pair(tileSheetDetails.m_name, TileSheet(textureManager, tileSheetDetails)).second

	if (m_tileSheets.find(tileSheetDetails.m_name) == m_tileSheets.cend())
	{
		m_tileSheets.emplace(std::make_pair(tileSheetDetails.m_name, TileSheet(tileSheetDetails)));
	}
}

void TileSheetManager::releaseTileSheet(const std::string & name)
{
	auto cIter = m_tileSheets.find(name);
	assert(cIter != m_tileSheets.cend());
	cIter->second.releaseTileSheetTexture();
}
