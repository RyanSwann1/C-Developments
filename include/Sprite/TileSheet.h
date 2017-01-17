#pragma once

#include "SharedContext.h"
#include "Managers\TextureManager.h"
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
	TileSheet(TextureManager& textureManager, const TileSheetDetails& details);
	
	const sf::Texture* const getTexture() const;
	inline const TileSheetDetails& getDetails() const { return m_details; }
	const sf::IntRect getTileLocationByID(const int ID) const;
	const sf::IntRect getTileLocationByPosition(const sf::IntRect& rect) const;
	inline void releaseTileSheetTexture() const { m_textureManager.releaseResource(m_details.m_name); }; //Maybe implement

private:
	TextureManager& m_textureManager;
	const TileSheetDetails m_details;
};