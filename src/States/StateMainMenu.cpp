#include "States\StateMainMenu.h"
#include <iostream>

StateMainMenu::StateMainMenu(StateManager& stateManager, const StateType type)
	: StateBase(stateManager, type)
{
}

void StateMainMenu::onEnter()
{
	std::cout << "This is the main menu!\n";
}

void StateMainMenu::onExit()
{
}

void StateMainMenu::update(const float deltaTime)
{
}

void StateMainMenu::draw(sf::RenderWindow & window)
{
}
