#pragma once
#include "Actor.h"
#include "Player.h"

class ActorBehavior {
public:
	ActorBehavior()
	{}

	/*ActorBehavior(std::shared_ptr<Actor> actor) 
		: _actor(actor)
	{}*/

	virtual void update(float dt, Actor* actor) = 0;

	virtual void apply(std::shared_ptr<Player> player) = 0;

protected:
	//std::shared_ptr<Actor> _actor;
};