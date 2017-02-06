#pragma once

#include "Managers/EventManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

struct StateManager;
class Window
{
public:
	Window(const StateManager& stateManager, const std::string& name = "SFML_WINDOW", const sf::Vector2i& size = sf::Vector2i(640, 480));

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	inline sf::RenderWindow& getWindow() { return m_window; }
	inline const bool isRunning() const { return m_window.isOpen(); }

	inline void beginDraw() { m_window.clear(sf::Color::Black); }
	inline void endDraw() { m_window.display(); }
	void toggleFullScreen();	
	void update();

private:
	EventManager m_eventManager;
	sf::RenderWindow m_window;
	const std::string m_name;
	const sf::Vector2i m_defaultSize;
	sf::Vector2i m_size;
	bool m_fullScreen;

	void setup();
	void create();

	inline void close() { m_window.close(); }
};
