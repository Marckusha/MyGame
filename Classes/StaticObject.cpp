#include "StaticObject.h"
#include "GameInfo.h"

USING_NS_CC;

const float SCALE = 30.f;

StaticObject::StaticObject() {}

StaticObject::StaticObject(const Vec2& position, const Vec2& size) {

	auto world = GameInfo::getInstance().getWorld();

	b2BodyDef bodyDef;
	bodyDef.position.Set(position.x / SCALE, position.y / SCALE);
	bodyDef.type = b2_staticBody;
	_body = world->CreateBody(&bodyDef);

	b2PolygonShape sh;
	sh.SetAsBox((size.x / 2.f) / SCALE, (size.y / 2.f) / SCALE);
	_shape = new b2PolygonShape(sh);

	b2FixtureDef fixDef;
	fixDef.shape = _shape;
	fixDef.friction = 1.f;
	_body->CreateFixture(&fixDef);

	sprite = Sprite::create("res/red.jpg", Rect(0, 0, size.x, size.y));
	sprite->setAnchorPoint(Vec2(0.5, 0.5));
	sprite->setPosition(position);
}