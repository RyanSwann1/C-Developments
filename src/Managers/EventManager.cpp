#include "Managers\EventManager.h"
#include "Locators\EventManagerLocator.h"
#include "Managers\StateManager.h"
#include "Utilities.h"
#include <algorithm>
#include <sstream>
#include <fstream>

EventManager::EventManager(const StateManager& stateManager)
	: m_bindings(),
	m_callBacks(),
	m_stateManager(stateManager)
{
	EventManagerLocator::provide(*this);
	loadInBindings();
}

void EventManager::update(const sf::Event & sfmlEvent)
{
	const EventType currentEvent = static_cast<EventType>(sfmlEvent.type);
	for (auto &i : m_bindings)
	{
		if (currentEvent == i.m_details.m_eventType && sfmlEvent.key.code == i.m_details.m_keyCode)
		{
			++i.m_count;
		}
	}
}

void EventManager::handleEvents()
{
	for (auto &i : m_bindings)
	{
		if (i.m_count > 0)
		{
			--i.m_count;
			activateCallBack(i.m_details);
		}
	}
}

void EventManager::activateCallBack(const EventDetails& details)
{
	auto cIter = m_callBacks.find(details.m_name);
	if (cIter != m_callBacks.cend())
	{
		if (m_stateManager.getCurrentStateType() == cIter->second.first)
		{
			cIter->second.second(details);
		}
	}
}

void EventManager::loadInBindings()
{
	std::ifstream file(Utilities::getEventDetails());
	assert(file.is_open());

	std::string line;
	while (std::getline(file, line))
	{
		if (line[0] == '|')
		{
			continue;
		}

		std::stringstream keyStream(line);
		std::string type;
		int name = 0, keyCode = 0, eventType = 0;

		keyStream >> name >> eventType >> keyCode;

		assert(registerBinding(name, keyCode, eventType));
	}
	int i = 0;
}

void EventManager::removeCallBack(const KeyBindingName name)
{
	auto iter = std::find_if(m_callBacks.begin(), m_callBacks.end(), [name](const auto& callBack) {return callBack.first == name; });
	if (iter != m_callBacks.cend())
	{
		m_callBacks.erase(iter);
	}
}

bool EventManager::registerBinding(const int name, const int keyCode, const int eventType)
{
	if (std::find_if(m_bindings.cbegin(), m_bindings.cend(), [name](const auto& binding) {return binding.m_details.m_name == static_cast<KeyBindingName>(name); }) == m_bindings.cend())
	{
		m_bindings.emplace_back(Binding(EventDetails(name, eventType, keyCode)));
		return true;
	}

	return false;
}
