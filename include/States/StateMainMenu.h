#pragma once

#include "States\StateBase.h"

class StateMainMenu : public StateBase
{
public:
	StateMainMenu(StateManager& stateManager, const StateType type);

	void onEnter() override;
	void onExit() override;

	void update(const float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

private:

};