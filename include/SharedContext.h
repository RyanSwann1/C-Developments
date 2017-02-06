#pragma once

class TextureManager;
class EntityManager;
class StateManager;
class WorldMap;
class TileSheetManager;
class EventManager;
class GameManager;
class LevelManager;
struct SharedContext
{
	SharedContext(StateManager& stateManager)
		: m_stateManager(stateManager),
		m_gameManager(nullptr),
		m_entityManager(nullptr),
		m_worldMap(nullptr)
	{}

	SharedContext(const SharedContext&) = delete;
	SharedContext& operator=(const SharedContext&) = delete;

	StateManager& m_stateManager;
	GameManager* m_gameManager;
	EntityManager* m_entityManager;
	WorldMap* m_worldMap;
};
