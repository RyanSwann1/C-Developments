#include "Managers\GameManager.h"
#include "Map\WorldMap.h"
#include "Managers\EntityManager.h"
#include "Entities\Player.h"
#include "Managers\LevelManager.h"
#include "Managers\StateManager.h"
#include "Tiles\LockTile.h"

GameManager::GameManager(SharedContext & sharedContext)
	: m_sharedContext(sharedContext)
{

}

void GameManager::update()
{
	
}

void GameManager::winGame(const LevelManager& levelManager)
{
	//Determines if any more levels to complete before winning the game
	if (!levelManager.levelsToComplete())
	{
		m_sharedContext.m_stateManager.switchTo(StateType::Win);
		m_sharedContext.m_stateManager.removeState(StateType::Game);
		//http://moonstoneequation.com/a-warning-to-others/
	}
}

void GameManager::endGame()
{
	m_sharedContext.m_stateManager.switchTo(StateType::MainMenu);
	m_sharedContext.m_stateManager.removeState(StateType::Game);
}

void GameManager::gameOver()
{
	m_sharedContext.m_stateManager.switchTo(StateType::MainMenu);
	m_sharedContext.m_stateManager.removeState(StateType::Game);
}