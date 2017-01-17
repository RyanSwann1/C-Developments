#pragma once

#include "Entities\Character.h"
struct EventDetails;
class Player : public Character
{
public:
	Player(SharedContext& sharedContext, const sf::Vector2f& pos, const int ID, const std::string& name);
	~Player();

	bool isHoldingKey() const { return m_holdingKey; }
	bool isOnNextLevelTile() const { return m_onNextLevelTile; }

	void reduceLife() override;
	void update(const float deltaTime) override final;
	void onEntityCollision(Entity& entity) override {}
	void onInteractiveTileCollision(InteractiveTile& tile) override;

private:
	bool m_holdingKey; //Player holding key
	bool m_onClimbableObject; //Player on tile that allows them to climb
	bool m_onNextLevelTile;

	void reactToInput(const EventDetails& eventDetails);
	void climb(const Direction dir);
	void respawn();
	void killCharacter() override;
};