#pragma once

#include <assert.h>
class EventManager;
class EventManagerLocator
{
public:
	static EventManager& getEventManager()
	{
		assert(m_eventManager);
		return *m_eventManager;
	}

	static void provide(EventManager& eventManager)
	{
		m_eventManager = &eventManager;
	}

private:
	EventManagerLocator() {}
	static EventManager* m_eventManager;
};