#include "ActorFactory.h"
#include "Actor.h"
#include "DamageBehavior.h"
#include "GameInfo.h"

USING_NS_CC;

std::shared_ptr<Actor> DamageFactory::createActor(const NPCInfo& info) {

	auto world = GameInfo::getInstance().getWorldForNPC();

	std::shared_ptr<DamageBehavior> behavior(new DamageBehavior(info.ways));
	std::shared_ptr<Actor> actor(new Actor(info.animationMap, info.startPosition, world));
	actor->setSpeed(info.speed);
	actor->setBehavior(behavior);

	return actor;

	/*_baseActor = std::shared_ptr<Actor>(new Actor(animMap, Vec2(700, 300), _worldForNPC));
	this->addChild(_baseActor->getSprite());
	_baseActor->setSpeed(Vec2(15.f, 0));

	
	std::shared_ptr<PeaceBehavior> _peaceBehavior(new PeaceBehavior(ways));
	//std::shared_ptr<DamageBehavior> _peaceBehavior(new DamageBehavior(ways));
	_baseActor->setBehavior(_peaceBehavior);*/
}