#pragma once

#include "Entities/EntityState.h"
#include <SFML/Graphics.hpp>
#include <string>

struct AnimationDetails;
class TileSheet;
class Animation
{
public:
	Animation(const AnimationDetails& details);

	inline bool isActive() const { return m_isPlaying; }
	inline bool isFinished() const { return m_isFinished; }
	inline bool isRepeatable() const { return m_repeatable; }
	inline const std::string& getName() const { return m_name; }
	inline const std::string& getTileSheetName() const { return m_tileSheetName; }
	sf::IntRect getDrawLocation() const;
	sf::Vector2f getPosition(const sf::Vector2f& pos) const;

	void play();
	void stop();
	inline void flip(const bool i) { m_isFlipped = i; }
	void update(const float deltaTime);

private:
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
	const bool m_reversible;
	bool m_reverse; //Reverse the animation
	bool m_isPlaying;
	
	inline void end() { m_isFinished = true; }
};
