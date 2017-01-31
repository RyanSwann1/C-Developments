#include "Managers/StateManager.h"
#include "States/StateBase.h"
#include "States/StateGame.h"
#include "States/StateMainMenu.h"
#include "States/StateWinGame.h"
#include <assert.h>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <assert.h>

class StateManager::StateFactory
{
public:
	StateFactory(StateManager* stateManager)
	{
		registerState<StateGame>(stateManager, StateType::Game);
		registerState<StateMainMenu>(stateManager, StateType::MainMenu);
		registerState<StateWinGame>(stateManager, StateType::Win);
	}

	StateBase* createState(const StateType stateType) const
	{
		auto cIter = m_stateFactory.find(stateType);
		assert(cIter != m_stateFactory.cend());
		return cIter->second();
	}

private:
	std::unordered_map<StateType, std::function<StateBase*()>> m_stateFactory;

	template <class T>
	void registerState(StateManager* stateManager, const StateType stateType)
	{
		assert(m_stateFactory.find(stateType) == m_stateFactory.cend());
		m_stateFactory.emplace(std::make_pair(stateType, [stateType, stateManager]() -> StateBase*
		{
			return new T(*stateManager, stateType);
		}));
	}
};

StateManager::StateManager(SharedContext & sharedContext)
	: m_stateFactory(new StateFactory(this)),
	m_states(),
	m_statesToRemove(),
	m_statesToAdd(),
	m_currentState(nullptr),
	m_sharedContext(sharedContext)
{
}

StateManager::~StateManager()
{
	purgeStates();
	delete m_stateFactory;
}

StateType StateManager::getCurrentStateType() const
{
	if (m_currentState)
	{
		return m_currentState->getType();
	}
	else
	{
		return StateType::None;
	}
}

void StateManager::switchTo(const StateType stateType)
{
	if (m_currentState && m_currentState->getType() != stateType)
	{
		m_currentState->onExit();
	}

	for (auto iter = m_states.begin(); iter != m_states.end(); ++iter)
	{
		if ((*iter)->getType() == stateType)
		{
			m_currentState = *iter;
			m_currentState->onEnter();
			return;
		}
	}

	stateToAdd(stateType);
}

void StateManager::removeState(const StateType stateType)
{
	if (std::find(m_statesToRemove.cbegin(), m_statesToRemove.cend(), stateType) == m_statesToRemove.cend())
	{
		m_statesToRemove.push_back(stateType);
	}
}

void StateManager::update(const float deltaTime)
{
	for (auto &i : m_states)
	{
		i->update(deltaTime);
	}
	
	processRemovals();
	processStatesToAdd();
}

void StateManager::draw(sf::RenderWindow& window)
{
	for (const auto &i : m_states)
	{
		i->draw(window);
	}
}

void StateManager::createState(const StateType stateType)
{
	StateBase* const state = m_stateFactory->createState(stateType);
	assert(state);

	m_states.emplace_back(state);
	state->onEnter();
	m_currentState = state;
}

void StateManager::processRemovals()
{
	if (m_statesToRemove.empty())
	{
		return;
	}

	for (auto iter = m_statesToRemove.begin(); iter != m_statesToRemove.end();)
	{
		if (removedActiveState(*iter))
		{
			iter = m_statesToRemove.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	//If any states remain
	m_statesToRemove.clear();
}

void StateManager::processStatesToAdd()
{
	if (m_statesToAdd.empty())
	{
		return;
	}

	for (const auto & i : m_statesToAdd)
	{
		createState(i);
	}
	m_statesToAdd.clear();
}

bool StateManager::removedActiveState(const StateType stateType)
{
	auto iter = std::find_if(m_states.begin(), m_states.end(), [stateType](StateBase* state) {return state->getType() == stateType; });
	if (iter != m_states.cend())
	{
		delete *iter;
		*iter = nullptr;
		m_states.erase(iter);
		return true;
	}
	return false;
}

void StateManager::stateToAdd(const StateType type)
{
	if (std::find(m_statesToAdd.cbegin(), m_statesToAdd.cend(), type) == m_statesToAdd.cend())
	{
		m_statesToAdd.push_back(type);
	}
}

void StateManager::purgeStates()
{
	for (auto &i : m_states)
	{
		delete i;
		i = nullptr;
	}
	m_states.clear();
}
