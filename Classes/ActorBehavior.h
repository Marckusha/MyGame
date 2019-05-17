#pragma once
#include "Actor.h"

class ActorBehavior {
public:
	ActorBehavior()
	{}

	ActorBehavior(std::shared_ptr<Actor> actor) 
		: _actor(actor)
	{}

	virtual void update(float dt) = 0;

protected:
	std::shared_ptr<Actor> _actor;
};