#pragma once

class Entity;

class Observer
{
public:
	virtual void onNotify(const Entity& entity) = 0;
};