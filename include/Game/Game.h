#pragma once

#include "SharedContext.h"
#include "Window\Window.h"
#include "Managers\StateManager.h"
#include "Managers\TextureManager.h"
#include "Managers\EntityManager.h"
#include "Map\WorldMap.h"
#include "Parser\GUIParser.h"
#include "Managers\TileSheetManager.h"
#include "Utilities.h"

class Game
{
public:
	Game();

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	const bool isRunning() const { return m_window.isRunning(); }
	void update();
	void draw();
	void lateUpdate();

private:
	SharedContext m_sharedContext;
	StateManager m_stateManager;
	TextureManager m_textureManager;
	GUIParser m_guiParser;
	WorldMap m_worldMap;
	
	EntityManager m_entityManager;
	TileSheetManager m_tileSheetManager;
	const Utilities m_utilities;
	Window m_window;

	sf::Time m_time;
	sf::Clock m_clock;
};