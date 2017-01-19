#include "..\..\include\Sprite\Animation.h"
#include "Sprite\TileSheet.h"
#include "Managers\TileSheetManager.h"
#include <assert.h>

//Animation::Animation(TileSheetManager& tileSheetManager, const int state, const std::string& tileSheetName, const int startRow, 
//	const int endRow, const int column, const int frameTime, const int repeatable, const sf::Vector2i& frameSize)
//	: m_startRow(startRow),
//	m_endRow(endRow),
//	m_column(column),
//	m_frameTime(frameTime),
//	m_repeatable(static_cast<bool>(repeatable)),
//	m_frameSize(frameSize),
//	m_tileSheet(nullptr),
//	m_isFinished(false),
//	m_isFlipped(false),
//	m_state(static_cast<EntityState>(state))
//{
//	const TileSheet* tileSheet = tileSheetManager.getTileSheet(tileSheetName);
//	if (tileSheet)
//	{
//		m_tileSheet = tileSheet;
//		m_sprite.setTexture(*m_tileSheet->getTexture());
//	}
//}

//TileSheetManager& m_tileSheetManager;
//const EntityState m_state;
//const int m_startRow;
//const int m_endRow;
//const int m_column;
//const int m_frameTime;
//const int m_repeatable;
//const sf::Vector2i& frameSize;
//
//float m_elaspedTime;
//int m_currentRow;
//bool m_isFinished;
//bool m_isFlipped;
//sf::Sprite m_sprite;
//inline void end() { m_isFinished = true; }

Animation::Animation(TileSheetManager & tileSheetManager, const std::string& name, const std::string & tileSheetName, const int startRow, 
	const int endRow, const int column, const float frameTime, const int repeatable, const sf::Vector2i & frameSize, const bool reversible)
	: m_tileSheetManager(tileSheetManager),
	m_name(name),
	m_startRow(startRow),
	m_endRow(endRow),
	m_column(column),
	m_frameTime(frameTime),
	m_repeatable(static_cast<bool>(repeatable)),
	m_frameSize(frameSize),
	m_tileSheetName(tileSheetName),
	m_elaspedTime(0),
	m_currentRow(startRow),
	m_isFinished(false),
	m_isFlipped(false),
	m_reversible(reversible),
	m_reverse(false),
	m_active(false)
{
	m_sprite.setTexture(*m_tileSheetManager.getTileSheet(m_tileSheetName).getTexture());
}

Animation::~Animation()
{
	m_tileSheetManager.releaseTileSheet(m_tileSheetName);
}

void Animation::setSpritePosition(const sf::Vector2f & newPos)
{
	//Hacky - i think..
	//Done so that it doesn't draw any other tile that it shouldnt on the tile sheet
	if (m_frameSize.y > 1)
	{
		const int tileSize = m_tileSheetManager.getTileSheet(m_tileSheetName).getDetails().m_tileSize;
		m_sprite.setPosition(sf::Vector2f(newPos.x, newPos.y - tileSize));
	}
	else
	{
		m_sprite.setPosition(newPos);
	}	
}

void Animation::play()
{
	m_active = true;
	m_isFinished = false;
}

void Animation::stop()
{
	m_active = false;
	m_isFinished = true;
	m_currentRow = m_startRow;
	m_elaspedTime = 0;
}

void Animation::update(const float deltaTime)
{
	m_elaspedTime += deltaTime;
	if (m_active && m_elaspedTime >= m_frameTime)
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
			m_active = m_repeatable;
			if (m_active)
			{
				m_isFinished = false;
				m_currentRow = m_startRow;
			}
		}
	}
}

void Animation::draw(sf::RenderWindow & window)
{
	//if (m_tileFlipped)
	//{
	//	m_spriteSheet.setTextureRect(sf::IntRect(drawLocation.x * tileSize, drawLocation.y * tileSize, tileSize, tileSize));
	//}
	//else
	//{
	//	m_spriteSheet.setTextureRect(sf::IntRect(drawLocation.x * tileSize, drawLocation.y * tileSize, -tileSize, tileSize));
	//}

	sf::IntRect rect = m_tileSheetManager.getTileSheet(m_tileSheetName).getTileLocationByPosition(
		sf::IntRect(m_currentRow, m_column, m_frameSize.x, m_frameSize.y));

	if (m_isFlipped)
	{
		//rect.width = -1.0f;
		
		//rect.width - 1.0f;
		//rect.height - 1.0f;
		//m_sprite.setScale(sf::Vector2f(-16, 0));
	}
	m_sprite.setTextureRect(rect);


	window.draw(m_sprite);
}