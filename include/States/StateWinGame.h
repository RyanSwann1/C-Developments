#pragma once
#include "States/StateBase.h"
class StateWinGame :
	public StateBase
{
public:
	StateWinGame(StateManager& stateManager, const StateType type);
	~StateWinGame();

	void update(const float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	void onEnter() override;
};
