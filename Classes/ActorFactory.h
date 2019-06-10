#pragma once
#include "NPCInfo.h"

class Actor;

class ActorFactory {
public:
	virtual std::shared_ptr<Actor> createActor(const NPCInfo&) = 0;

	virtual ~ActorFactory() {}
};

class DamageFactory : public ActorFactory {
public:
	virtual std::shared_ptr<Actor> createActor(const NPCInfo&) override;

	virtual ~DamageFactory() {}
};