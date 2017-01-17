#pragma once


#include "Events\Binding.h"
#include "SharedContext.h"
#include "States\StateType.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

using CallBack = std::pair<StateType, std::function<void(const EventDetails&)>>;
using std::placeholders::_1;

class EventManager
{
public:
	EventManager(SharedContext& sharedContext);

	template <class T>
	void addCallBack(const KeyBindingName name, const StateType type, void(T::*fp)(const EventDetails&), T* const instance)
	{
		if (m_callBacks.find(name) == m_callBacks.cend())
		{
			auto callBack = std::bind(fp, instance, _1);
			//auto callBack = std::make_pair(type, std::bind(fp, instance, _1));
			m_callBacks.emplace(name, std::make_pair(type, callBack));
		}
	}

	void removeCallBack(const KeyBindingName name);

	void update(const sf::Event& sfmlEvent);
	void handleEvents();

private:
	std::vector<Binding> m_bindings;
	std::unordered_map<KeyBindingName, CallBack> m_callBacks;
	SharedContext& m_sharedContext;

	const bool registerBinding(const int name, const int keyCode, const int eventType);
	void loadInBindings(const std::string& fileName);
	
	void activateCallBack(const EventDetails& details);
};