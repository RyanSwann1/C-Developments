#pragma once

#include "SharedContext.h"
#include "Window/Window.h"
#include "Managers/StateManager.h"
#include "Managers/TextureManager.h"
#include "Managers/EntityManager.h"
#include "Managers/TileSheetManager.h"
#include "Map/WorldMap.h"

#include "Managers/GameManager.h"
#include "Utilities.h"

class Game
{
public:
	Game();

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	inline bool isRunning() const { return m_window.isRunning(); }
	void update();
	void draw();
	void lateUpdate();

private:
	SharedContext m_sharedContext;
	TextureManager m_textureManager;
	Window m_window;
	StateManager m_stateManager;

	sf::Time m_time;
	sf::Clock m_clock;
};