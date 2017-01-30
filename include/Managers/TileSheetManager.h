#pragma once

#include "Sprite/TileSheet.h"
#include <string>
#include <unordered_map>

struct TileSheetDetails;
class TileSheetManager
{
public:
	TileSheetManager();

	TileSheet& getTileSheet(const std::string& name);
	void addTileSheet(const TileSheetDetails& tileSheetDetails);
	void releaseTileSheet(const std::string& name);

private:
	std::unordered_map<std::string, TileSheet> m_tileSheets;
};