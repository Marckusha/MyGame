#include "DynamicObject.h"
#include "GameInfo.h"

USING_NS_CC;

DynamicObject::DynamicObject() {}

DynamicObject* DynamicObject::createObject() {
	DynamicObject* platformetObject = new DynamicObject();
	platformetObject->autorelease();
	return platformetObject;
}

DynamicObject* DynamicObject::createObject(const std::string& fileName) {
	DynamicObject* platformetObject = new DynamicObject();
	platformetObject->initWithFile(fileName);
	platformetObject->autorelease();
	return platformetObject;
}

DynamicObject* DynamicObject::createWithSpriteFrameName(const std::string& spriteFrameName) {
	DynamicObject* platformetObject = new DynamicObject();
	platformetObject->initWithSpriteFrameName(spriteFrameName);
	platformetObject->autorelease();
	return platformetObject;
}

bool DynamicObject::init(const Vec2& position, const Vec2& size) {

	if (!PlatformerObject::init(position, size)) {
		return false;
	}

	auto world = GameInfo::getInstance().getWorld();
	auto SCALE = GameInfo::getInstance().getScaleWorld();

	b2BodyDef bodyDef;
	bodyDef.position.Set(position.x / SCALE, position.y / SCALE);
	bodyDef.type = b2_kinematicBody;

	_body = world->CreateBody(&bodyDef);

	b2PolygonShape sh;
	sh.SetAsBox((size.x / 2.f) / SCALE, (size.y / 2.f) / SCALE);
	_shape = new b2PolygonShape(sh);

	b2FixtureDef fixDef;
	fixDef.restitution = 0.f;
	fixDef.friction = 1000.f;
	fixDef.shape = _shape;
	_body->CreateFixture(&fixDef);
}

void DynamicObject::initBehavior(const std::shared_ptr<BehaviorDynamicObject>& behavior) { 
	_behavior = behavior; 
	_behavior->setBody(_body);
}

/*void DynamicObject::setLinearVelocity(const cocos2d::Vec2& velocity) {
	_body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}*/

void DynamicObject::update(float dt) {

	_behavior->update(dt);

	auto pos = _body->GetPosition();
	//TODO 
	///придумать без кэш промахов способ
	auto SCALE = GameInfo::getInstance().getScaleWorld();

	this->setPosition(Vec2(pos.x * SCALE, pos.y * SCALE));
}