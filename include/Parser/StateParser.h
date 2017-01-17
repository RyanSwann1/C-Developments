#pragma once

#include "SharedContext.h"
#include <string>

class StateManager;
class StateParser
{
public:
	StateParser(StateManager& stateManager);

	void parseStates();

private:
	StateManager* m_stateManager;

	void registerState(const std::string& stateName);
};