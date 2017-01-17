#pragma once

#include "Entities\EntityState.h"
#include "Managers\TileSheetManager.h"
#include <SFML\Graphics.hpp>
#include <string>

class TileSheet;
class Animation
{
public:

	Animation(TileSheetManager& tileSheetManager, const std::string& name, const std::string& tileSheetName, const int startRow, 
		const int endRow, const int column, const float frameTime, const int repeatable, const sf::Vector2i& frameSize, const bool reversible);
	~Animation();

	inline const bool isActive() const { return m_active; }
	inline const bool isFinished() const { return m_isFinished; }
	inline const bool isRepeatable() const { return m_repeatable; }
	inline const std::string& getName() const { return m_name; }
	inline sf::Vector2f& getPosition() { return m_position; }

	void setSpritePosition(const sf::Vector2f& pos);

	void play();
	void stop();
	inline void flip(const bool i) { m_isFlipped = i; }
	void update(const float deltaTime);
	void draw(sf::RenderWindow& window);

private:
	TileSheetManager& m_tileSheetManager;
	const std::string m_name;
	const int m_startRow;
	const int m_endRow;
	const int m_column;
	const float m_frameTime;
	const bool m_repeatable;
	const sf::Vector2i m_frameSize;
	const std::string m_tileSheetName;
	
	float m_elaspedTime;
	int m_currentRow;
	bool m_isFinished;
	bool m_isFlipped;
	sf::Sprite m_sprite;
	//TileSheet& m_tileSheet;
	const bool m_reversible;
	bool m_reverse; //Reverse the animation
	bool m_active;
	sf::Vector2f m_position;
	
	inline void end() { m_isFinished = true; }
};