#include "Animations/Animation.h"
#include "Sprite/TileSheet.h"
#include "Managers/TileSheetManager.h"
#include "Locators/TileSheetManagerLocator.h"
#include <assert.h>
#include "Animations/AnimationDetails.h"

Animation::Animation(const AnimationDetails & details)
	: m_name(details.m_name),
	m_startRow(details.m_startRow),
	m_endRow(details.m_endRow),
	m_column(details.m_column),
	m_frameTime(details.m_frameTime),
	m_repeatable(details.m_repeatable),
	m_frameSize(details.m_frameSize),
	m_tileSheetName(details.m_tileSheetName),
	m_elaspedTime(0),
	m_currentRow(m_startRow),
	m_isFinished(false),
	m_isFlipped(false),
	m_reversible(details.m_reversible),
	m_reverse(false),
	m_isPlaying(false)
{}

//TileSheetManager& m_tileSheetManager;
//const std::string m_name;
//const int m_startRow;
//const int m_endRow;
//const int m_column;
//const float m_frameTime;
//const bool m_repeatable;
//const sf::Vector2i m_frameSize;
//const std::string m_tileSheetName;
//
//float m_elaspedTime;
//int m_currentRow;
//bool m_isFinished;
//bool m_isFlipped;
//sf::Sprite m_sprite;
//const bool m_reversible;
//bool m_reverse; //Reverse the animation
//bool m_active;

//Animation::Animation(TileSheetManager & tileSheetManager, const std::string& name, const std::string & tileSheetName, const int startRow,
//	const int endRow, const int column, const float frameTime, const int repeatable, const sf::Vector2i & frameSize, const bool reversible)
//	: m_tileSheetManager(tileSheetManager),
//	m_name(name),
//	m_startRow(startRow),
//	m_endRow(endRow),
//	m_column(column),
//	m_frameTime(frameTime),
//	m_repeatable(static_cast<bool>(repeatable)),
//	m_frameSize(frameSize),
//	m_tileSheetName(tileSheetName),
//	m_elaspedTime(0),
//	m_currentRow(startRow),
//	m_isFinished(false),
//	m_isFlipped(false),
//	m_reversible(reversible),
//	m_reverse(false),
//	m_active(false)
//{
//	m_sprite.setTexture(*m_tileSheetManager.getTileSheet(m_tileSheetName).getTexture());
//}

sf::IntRect Animation::getDrawLocation() const
{
	return TileSheetManagerLocator::getTileSheetManager().getTileSheet(m_tileSheetName).getTileLocationByPosition(sf::IntRect(
		sf::Vector2i(m_currentRow, m_column), sf::Vector2i(m_frameSize.x, m_frameSize.y)));
}

sf::Vector2f Animation::getPosition(const sf::Vector2f & newPos) const
{
	//Hacky - i think..
	//Done so that it doesn't draw any other tile that it shouldnt on the tile sheet
	if (m_frameSize.y > 1)
	{
		const int tileSize = TileSheetManagerLocator::getTileSheetManager().getTileSheet(m_tileSheetName).getDetails().m_tileSize;
		return sf::Vector2f(newPos.x, newPos.y - tileSize);
		//m_sprite.setPosition(sf::Vector2f(newPos.x, newPos.y - tileSize));
	}
	else
	{
		return sf::Vector2f(newPos);
	}	
}

void Animation::play()
{
	m_isPlaying = true;
	m_isFinished = false;
}

void Animation::stop()
{
	m_isPlaying = false;
	m_isFinished = true;
	m_currentRow = m_startRow;
	m_elaspedTime = 0;
}

void Animation::update(const float deltaTime)
{
	if (!m_isPlaying)
	{
		return;
	}

	m_elaspedTime += deltaTime;
	if (m_isPlaying && m_elaspedTime >= m_frameTime)
	{
		m_elaspedTime = 0;
		
		if (!m_isFinished && m_reversible)
		{
			if (!m_reverse && m_currentRow < m_endRow)
			{
				++m_currentRow;
				if (m_currentRow == m_endRow) 
				{
					m_reverse = true;
				}
			}
			else if (m_reverse && m_currentRow > m_startRow)
			{
				--m_currentRow;
				if (m_currentRow == m_startRow)
				{
					m_reverse = false;
					m_isFinished = true;
				}
			}
		}
		else if (!m_isFinished)
		{
			if (m_currentRow < m_endRow)
			{
				++m_currentRow;
				if (m_currentRow == m_endRow)
				{
					m_isFinished = true;
				}
			}
		}

		if (m_isFinished)
		{
			m_isPlaying = m_repeatable;
			if (m_isPlaying)
			{
				m_isFinished = false;
				m_currentRow = m_startRow;
			}
			else
			{
				stop();
			}
		}
	}
}

//void Animation::draw(sf::RenderWindow & window)
//{
//	//if (m_tileFlipped)
//	//{
//	//	m_spriteSheet.setTextureRect(sf::IntRect(drawLocation.x * tileSize, drawLocation.y * tileSize, tileSize, tileSize));
//	//}
//	//else
//	//{
//	//	m_spriteSheet.setTextureRect(sf::IntRect(drawLocation.x * tileSize, drawLocation.y * tileSize, -tileSize, tileSize));
//	//}
//
//	sf::IntRect rect = m_tileSheetManager.getTileSheet(m_tileSheetName).getTileLocationByPosition(
//		sf::IntRect(m_currentRow, m_column, m_frameSize.x, m_frameSize.y));
//
//	if (m_isFlipped)
//	{
//		//rect.width = -1.0f;
//		
//		//rect.width - 1.0f;
//		//rect.height - 1.0f;
//		//m_sprite.setScale(sf::Vector2f(-16, 0));
//	}
//	m_sprite.setTextureRect(rect);
//
//
//	window.draw(m_sprite);
//}