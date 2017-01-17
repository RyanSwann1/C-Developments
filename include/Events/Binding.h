#pragma once

#include "Events\EventType.h"
#include "Events\EventDetails.h"
#include <string>

struct Binding
{
	Binding(const EventDetails& eventDetails)
		: m_details(eventDetails),
		m_count(0)
	{}

	const EventDetails m_details;
	int m_count; //Represents what binding is currently in use if over 0
};