#pragma once

#include "SharedContext.h"
#include <string>
#include <unordered_map>
#include <functional>

template <class Object, class ObjectIdentifier>
class Factory
{
	friend class StateManager;
	friend class EntityManager;
public:
	Object* createObject(const ObjectIdentifier id)
	{
		auto cIter = m_objects.find(id);
		if (cIter != m_objects.cend())
		{
			return cIter->second();
		}
		return nullptr;
	}
	
private:
	std::unordered_map<ObjectIdentifier, std::function<Object*()>> m_objects; //Objects within the factory

	template <class DerivedObject>
	void registerObject(const ObjectIdentifier id, const SharedContext& sharedContext)
	{
		if (m_objects.find(id) == m_objects.cend())
		{
			m_objects.emplace(std::make_pair(id, [sharedContext]() -> Object*
			{
				return new DerivedObject*(sharedContext);
			}));
		}
	}
};

