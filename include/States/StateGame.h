#pragma once

#include "States\StateBase.h"
#include "Managers\LevelManager.h"
#include "Managers\GameManager.h"

class StateGame : public StateBase
{
public:
	StateGame(StateManager& stateManager, const StateType type);

	void onEnter() override;
	void onExit() override;

	void update(const float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

private:
	LevelManager m_levelManager;
	GameManager m_gameManager;
};