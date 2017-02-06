#pragma once

class WorldMap;
class EntityManager;
class GameManager;
#include <string>

void parseLevel(GameManager& gameManager, WorldMap& worldMap, EntityManager& entityManager, const std::string& levelName);
