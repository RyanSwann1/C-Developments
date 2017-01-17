#pragma once

#include <SFML\Graphics.hpp>

enum class EventType
{
	KeyDown = sf::Event::EventType::KeyPressed,
	KeyReleased = sf::Event::EventType::KeyReleased,
	Closed = sf::Event::EventType::Closed,
	MouseButtonDown = sf::Event::EventType::MouseButtonPressed,
	MouseButtonUp = sf::Event::EventType::MouseButtonReleased
};