#include "States/StateWinGame.h"
#include <iostream>

StateWinGame::StateWinGame(StateManager& stateManager, const StateType type)
	:StateBase(stateManager, type)
{
	std::cout << "Game has been won.\n";
}

StateWinGame::~StateWinGame()
{
}

void StateWinGame::update(const float deltaTime)
{
}

void StateWinGame::draw(sf::RenderWindow & window)
{
}

void StateWinGame::onEnter()
{
	std::cout << "Game Won.\n";
	std::cout << StateBase::getStateManager().getStateCount() << "\n";
}
