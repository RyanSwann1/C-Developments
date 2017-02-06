#include "States/StateGame.h"
#include "Managers/StateManager.h"
#include "Locators/TextureManagerLocator.h"
#include "Locators/TileSheetManagerLocator.h"

StateGame::StateGame(StateManager& stateManager, const StateType type)
	: StateBase(stateManager, type),
	m_tileSheetManager(),
	m_worldMap(),
	m_entityManager(m_gameManager, m_worldMap),
	m_gameManager(stateManager, m_worldMap, m_entityManager)
{
	SharedContext& sharedContext = stateManager.getSharedContext();
	sharedContext.m_worldMap = &m_worldMap;
	sharedContext.m_gameManager = &m_gameManager;
	sharedContext.m_entityManager = &m_entityManager;
}

StateGame::~StateGame()
{
	SharedContext& sharedContext = StateBase::getStateManager().getSharedContext();
	sharedContext.m_worldMap = nullptr;
	sharedContext.m_gameManager = nullptr;
	sharedContext.m_entityManager = nullptr;
}

void StateGame::onEnter()
{

}

void StateGame::onExit()
{

}

void StateGame::update(const float deltaTime)
{
	m_gameManager.update(deltaTime);
	m_entityManager.update(deltaTime);
}

void StateGame::draw(sf::RenderWindow & window)
{
	m_gameManager.draw(window);
	m_entityManager.draw(window);
}
