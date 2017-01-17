#pragma once

#include <SFML\Graphics.hpp>
#include "LayerType.h"
#include "SharedContext.h"

class Layer
{
public:
	Layer(const LayerType layerType, const SharedContext& sharedContext)
		: m_layerType(layerType),
		m_sharedContext(sharedContext)
	{}

	virtual void update(const float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

	const LayerType getLayerType() const { return m_layerType; }

protected:
	SharedContext& getSharedContext() { return m_sharedContext; }

private:
	const LayerType m_layerType;
	SharedContext m_sharedContext;
};