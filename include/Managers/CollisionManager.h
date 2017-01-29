#pragma once

class EntityManager;
class WorldMap;
class Entity;

void updateCollisions(const EntityManager& entityManager, WorldMap& worldMap, Entity& entity);