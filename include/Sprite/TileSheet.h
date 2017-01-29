#pragma once

#include "Sprite\TileSheetDetails.h"

#include <unordered_map>
#include <SFML\Graphics.hpp>
#include <string>
#include <vector>
#include <assert.h>

//Class to be used to interact with the TileSheet/SpriteSheet
class TileSheet
{
public:
	TileSheet(const TileSheetDetails& details);
	
	const sf::Texture* const getTexture() const;
	inline const TileSheetDetails& getDetails() const { return m_details; }
	sf::IntRect getTileLocationByID(const int ID) const;
	sf::IntRect getTileLocationByPosition(const sf::IntRect& rect) const;
	void releaseTileSheetTexture() const;

private:
	const TileSheetDetails m_details;
};