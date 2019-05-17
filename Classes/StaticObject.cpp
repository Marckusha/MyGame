#include "StaticObject.h"
#include "GameInfo.h"

USING_NS_CC;

StaticObject::StaticObject() {}

StaticObject* StaticObject::createObject() {
	StaticObject* platformetObject = new StaticObject();
	platformetObject->autorelease();
	return platformetObject;
}

StaticObject* StaticObject::createObject(const std::string& fileName) {
	StaticObject* platformetObject = new StaticObject();
	platformetObject->initWithFile(fileName);
	platformetObject->autorelease();
	return platformetObject;
}

StaticObject* StaticObject::createWithSpriteFrameName(const std::string& spriteFrameName) {
	StaticObject* platformetObject = new StaticObject();
	platformetObject->initWithSpriteFrameName(spriteFrameName);
	platformetObject->autorelease();
	return platformetObject;
}

bool StaticObject::init(const Vec2& position, const Vec2& size) {

	if (!PlatformerObject::init(position, size)) {
		return false;
	}

	auto world = GameInfo::getInstance().getWorld();
	auto worldNPC = GameInfo::getInstance().getWorldForNPC();

	auto SCALE = GameInfo::getInstance().getScaleWorld();

	b2BodyDef bodyDef;
	bodyDef.position.Set(position.x / SCALE, position.y / SCALE);
	bodyDef.type = b2_staticBody;
	_body = world->CreateBody(&bodyDef);
	_body2 = worldNPC->CreateBody(&bodyDef);

	b2PolygonShape sh;
	sh.SetAsBox((size.x / 2.f) / SCALE, (size.y / 2.f) / SCALE);
	_shape = new b2PolygonShape(sh);

	b2FixtureDef fixDef;
	fixDef.shape = _shape;
	fixDef.friction = 1.f;
	_body->CreateFixture(&fixDef);
	_body2->CreateFixture(&fixDef);

	return true;
}