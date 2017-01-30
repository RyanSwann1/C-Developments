#include "Window/Window.h"

Window::Window(const StateManager& stateManager, const std::string & name, const sf::Vector2i & size)
	: m_name(name),
	m_defaultSize(size),
	m_fullScreen(false),
	m_eventManager(stateManager)
{

	setup();
}

void Window::toggleFullScreen()
{
	(m_fullScreen ? m_fullScreen = false : m_fullScreen = true);
}

void Window::update()
{
	sf::Event sfmlEvent;
	while (m_window.pollEvent(sfmlEvent))
	{
		if (sfmlEvent.Closed)
		{
			close();
		}

		m_eventManager.update(sfmlEvent);
	}
	m_eventManager.handleEvents();
}

void Window::setup()
{
	m_size = m_defaultSize;
	create();
}

void Window::create()
{
	auto style = sf::Style::Default;
	m_window.create(sf::VideoMode(m_size.x, m_size.y), m_name, style);
}
