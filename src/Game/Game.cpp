#include "Game/Game.h"
#include "Locators/TileSheetManagerLocator.h"

Game::Game() 
	: m_sharedContext(m_stateManager),
	m_textureManager(),
	m_window(m_stateManager),
	m_stateManager(m_sharedContext),
	m_time(),
	m_clock()
{
	m_stateManager.switchTo(StateType::Game);
}

void Game::update()
{
	m_window.update();
	m_stateManager.update(m_time.asSeconds());
}

void Game::draw()
{
	m_window.beginDraw();
	m_stateManager.draw(m_window.getWindow());
	m_window.endDraw();
}

void Game::lateUpdate()
{
	m_time = m_clock.restart();
}