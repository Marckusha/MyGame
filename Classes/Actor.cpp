#include "Actor.h"
#include "GameInfo.h"
#include "ActorBehavior.h"

USING_NS_CC;

Actor::Actor(const AnimationMap& animMap, const Vec2& position, std::shared_ptr<b2World> world)
	: BaseActor(animMap, position, world)
{}

void Actor::update(float dt) {
	BaseActor::update(dt);
	if (_behavior) {
		_behavior->update(dt);
	}
}

void Actor::moveToLeft() {
	sprite->stopAllActions();

	_body->SetLinearVelocity(b2Vec2(-_speed.x, 0.f));
	_setAnimation("run");
	sprite->setRotationSkewY(180);
}

void Actor::moveToRight() {
	sprite->stopAllActions();

	_body->SetLinearVelocity(b2Vec2(_speed.x, 0.f));
	_setAnimation("run");
	sprite->setRotationSkewY(0);
}
void Actor::stop() {
	sprite->stopAllActions();

	_body->SetLinearVelocity(b2Vec2(0.f, 0.f));
	_setAnimation("idle");
}