#pragma once

#include "KeyBindingName.h"
#include "EventType.h"

struct EventDetails
{
	EventDetails(const int name, const int type, const int keyCode)
		: m_name(static_cast<KeyBindingName>(name)),
		m_eventType(static_cast<EventType>(type)),
		m_keyCode(keyCode)
	{}

	const KeyBindingName m_name;
	const EventType m_eventType;
	const int m_keyCode;
};