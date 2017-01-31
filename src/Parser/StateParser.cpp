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
}

void StateParser::registerState(const std::string & stateName)
{

}
