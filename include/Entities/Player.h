#pragma once

#include "Entities/Character.h"

struct EventDetails;
class Player : public Character
{
public:
	Player(GameManager& gameManager, WorldMap& worldMap, EntityManager& entityManager, const sf::Vector2f& pos, const int ID, const std::string& name, const EntityType type);
	~Player() override;

	bool isHoldingKey() const { return m_holdingKey; }
	bool isOnNextLevelTile() const { return m_onNextLevelTile; }

	void reduceLife() override final;
	void increaseScore(const int i);
	void onEntityCollision(Entity& entity) override {}
	void onInteractiveTileCollision(InteractiveTile& tile) override ;

private:
	bool m_holdingKey; //Player holding key
	bool m_onClimbableObject; //Player on tile that allows them to climb
	bool m_onNextLevelTile;
	int m_score;

	void reactToInput(const EventDetails& eventDetails);
	void climb(const Direction dir);
	void respawn();
	void killCharacter() override;
};