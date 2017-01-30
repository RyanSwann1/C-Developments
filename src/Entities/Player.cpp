#include "Entities/Player.h"
#include "Managers/EventManager.h"
#include "Map/InteractiveTileLayer.h"
#include "Tiles/TileType.h"
#include "Managers/GameManager.h"
#include "Tiles/DoorTile.h"
#include "Map/WorldMap.h"
#include "Locators/EventManagerLocator.h"
#include <iostream>
#include <assert.h>

Player::Player(GameManager & gameManager, WorldMap & worldMap, EntityManager & entityManager, const sf::Vector2f & pos, const int ID, const std::string & name, const EntityType type)
	: Character(gameManager, worldMap, entityManager, pos, ID, name, type),
	m_holdingKey(false),
	m_onClimbableObject(false),
	m_onNextLevelTile(false),
	m_score(0)
{
	EventManager& eventManager = EventManagerLocator::getEventManager();
	eventManager.addCallBack<Player>(KeyBindingName::Move_Left, StateType::Game, &Player::reactToInput, this);
	eventManager.addCallBack<Player>(KeyBindingName::Move_Right, StateType::Game, &Player::reactToInput, this);
	eventManager.addCallBack<Player>(KeyBindingName::Move_Up, StateType::Game, &Player::reactToInput, this);
	eventManager.addCallBack<Player>(KeyBindingName::Move_Down, StateType::Game, &Player::reactToInput, this);
	eventManager.addCallBack<Player>(KeyBindingName::Jump, StateType::Game, &Player::reactToInput, this);
}

Player::~Player()
{
	EventManager& eventManager = EventManagerLocator::getEventManager();
	eventManager.removeCallBack(KeyBindingName::Move_Left);
	eventManager.removeCallBack(KeyBindingName::Move_Right);
	eventManager.removeCallBack(KeyBindingName::Move_Up);
	eventManager.removeCallBack(KeyBindingName::Move_Down);
	eventManager.removeCallBack(KeyBindingName::Jump);
}

void Player::reactToInput(const EventDetails& eventDetails)
{
	switch (eventDetails.m_name)
	{
	case (KeyBindingName::Move_Left):
	{
		Entity::moveInDirection(Direction::Left);
		break;
	}
	case (KeyBindingName::Move_Right):
	{
		Entity::moveInDirection(Direction::Right);
		break;
	}
	case (KeyBindingName::Jump):
	{
		Character::jump();
		break;
	}
	case (KeyBindingName::Move_Up) :
	{
		climb(Direction::Up);
		break;
	}
	case (KeyBindingName::Move_Down) :
	{
		climb(Direction::Down);
		break;
	}
	}
}

void Player::onInteractiveTileCollision(InteractiveTile & tile)
{
	//Reset checks
	m_onNextLevelTile = false;
	m_onClimbableObject = false;

	switch (tile.getType())
	{
	case (TileType::Bouncy) :
	{
		Character::doubleJump();
		tile.activate(*this);
		break;
	}
	case (TileType::Key) :
	{
		m_holdingKey = true;
		tile.activate(*this);
		break;
	}
	case (TileType::Ladder) :
	{
		m_onClimbableObject = true;
		Entity::setOnTile(true);
		break;
	}
	case (TileType::Lock) :
	{
		tile.activate(*this);
		
		if (m_holdingKey)
		{
			m_holdingKey = false;
		}
		break;
	}
	case (TileType::Door) :
	{
		m_onNextLevelTile = true;
		DoorTile& door = *static_cast<DoorTile*>(&tile);
		if (door.isOpen())
		{
			Entity::getGameManager().loadNextLevel(door, *this);
		}
		break;
	}
	case (TileType::Coin) :
	{
		tile.activate(*this);
		break;
	}
	case (TileType::CoinDispenser) :
	{
		tile.activate(*this);
		break;
	}
	}
}

void Player::climb(const Direction dir)
{
	if (!m_onClimbableObject)
	{
		return;
	}

	switch (dir)
	{
	case (Direction::Up) :
	{
		Entity::moveInDirection(Direction::Up);
		break;
	}
	case (Direction::Down) :
	{
		Entity::moveInDirection(Direction::Down);
		break;
	}
	}
}

void Player::reduceLife()
{
	Character::reduceLife();

	if (Character::getCurrentLives() > 0)
	{
		respawn();
	}
	else
	{
		killCharacter();
	}
}

void Player::increaseScore(const int i)
{
	m_score += i;
}

void Player::respawn()
{
	Entity::setPosition(sf::Vector2f(0, 0));
}

void Player::killCharacter()
{
	Character::killCharacter();
	Entity::getGameManager().endGame();
}
