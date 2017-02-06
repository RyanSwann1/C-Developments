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

