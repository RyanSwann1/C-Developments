#pragma once

#include <assert.h>

class TileSheetManager;
class TileSheetManagerLocator
{
public:
	static void provide(TileSheetManager& tileSheetManager)
	{
		m_tileSheetManager = &tileSheetManager;
	}

	static TileSheetManager& getTileSheetManager()
	{
		assert(m_tileSheetManager);
		return *m_tileSheetManager;
	}

private:
	TileSheetManagerLocator() {}
	static TileSheetManager* m_tileSheetManager;
};