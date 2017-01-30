#pragma once

#include "States/StateBase.h"
#include "Managers/GameManager.h"
#include "Map/WorldMap.h"
#include "Managers/EntityManager.h"
#include "Managers/TileSheetManager.h"

class StateGame : public StateBase
{
public:
	StateGame(StateManager& stateManager, const StateType type);
	~StateGame() override;

	void onEnter() override;
	void onExit() override;

	void update(const float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

private:
	TileSheetManager m_tileSheetManager;
	WorldMap m_worldMap;
	EntityManager m_entityManager;
	GameManager m_gameManager;
};