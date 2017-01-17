#include "States\StateGame.h"
#include "Managers\StateManager.h"
#include "Managers\TextureManager.h"

StateGame::StateGame(StateManager& stateManager, const StateType type)
	: StateBase(stateManager, type),
	m_levelManager(stateManager.getSharedContext()),
	m_gameManager(stateManager.getSharedContext())
{
	stateManager.getSharedContext().m_gameManager = &m_gameManager;
	stateManager.getSharedContext().m_levelManager = &m_levelManager;
}

void StateGame::onEnter()
{

}

void StateGame::onExit()
{

}

void StateGame::update(const float deltaTime)
{
	m_levelManager.update(deltaTime);
	m_gameManager.update();
}

void StateGame::draw(sf::RenderWindow & window)
{
	m_levelManager.draw(window);
}
