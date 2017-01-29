#pragma once

#include "States\StateType.h"
#include "SharedContext.h"
#include <vector>
#include <SFML\Graphics.hpp>

class StateBase;
class StateManager
{
public:
	StateManager(SharedContext& sharedContext);
	~StateManager();

	SharedContext& getSharedContext() const { return m_sharedContext; }
	StateType getCurrentStateType() const;

	void switchTo(const StateType stateType);
	void update(const float deltaTime);
	void draw(sf::RenderWindow& window);
	void removeState(const StateType stateType);
	int getStateCount() { return m_states.size(); }
private:
	class StateFactory;
	const StateFactory* const m_stateFactory;
	std::vector<StateBase*> m_states;
	std::vector<StateType> m_statesToRemove;
	std::vector<StateType> m_statesToAdd;
	StateBase* m_currentState;
	SharedContext& m_sharedContext;

	void createState(const StateType stateType);
	void processRemovals();
	void processStatesToAdd();
	void purgeStates();
	void stateToAdd(const StateType type);
	bool removedActiveState(const StateType stateType);
};
