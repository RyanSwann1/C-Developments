#include "Parser/StateParser.h"
#include "Managers/StateManager.h"
#include "XML/tinyxml.h"
#include "States/StateGame.h"


StateParser::StateParser(StateManager& stateManager)
	: m_stateManager(&stateManager)
{

}

void StateParser::parseStates()
{

	//m_stateManager->registerState<StateGame>(StateType::Game);
}

void StateParser::registerState(const std::string & stateName)
{

}
