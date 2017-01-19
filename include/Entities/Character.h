#pragma once

#include "Entities\Entity.h"
#include "Entities\EntityState.h"
#include "Timer.h"

class Character : public Entity
{
public:
	Character(SharedContext& sharedContext, const EntityType type, const sf::Vector2f& pos, const int ID, const std::string& name);

	void update(const float deltaTime) override;
	void handleTileCollisions(const std::vector<CollisionElement*>& collisions) override;
	virtual void reduceLife();

protected:
	int getCurrentLives() const { return m_lives; }
	void jump();
	void doubleJump();
	virtual void killCharacter(); //Set to destroy this character
	void attack();

private:
	Timer m_jumpingTimer;
	Timer m_doubleJumpTimer;
	Timer m_hurtTimer;
	EntityState m_currentState;
	//AttackManager m_attackManager;
	sf::FloatRect m_attackAABB;

	void determineAnimationType();
	EntityState m_state;
	void setState(const EntityState state);

	void loadInCharacterDetails();

	int m_maxLives;
	int m_lives;
	int m_damage;
	float m_hurtTime;
	float m_jumpTime;
	float m_doubleJumpTime;
	float m_jumpVelocity;
	bool m_jumpReady;
	bool m_climbingReady;

	void handleTimers(const float deltaTime);
	void checkBounds();
};