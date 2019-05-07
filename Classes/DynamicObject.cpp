#include "DynamicObject.h"
#include "GameInfo.h"

USING_NS_CC;

const float SCALE = 30.f;

DynamicObject::DynamicObject() {}

DynamicObject::DynamicObject(const Vec2& position, const Vec2& size) {

	auto world = GameInfo::getInstance().getWorld();

	b2BodyDef bodyDef;
	bodyDef.position.Set(position.x / SCALE, position.y / SCALE);
	bodyDef.type = b2_kinematicBody;
	_body = world->CreateBody(&bodyDef);

	b2PolygonShape sh;
	sh.SetAsBox((size.x / 2.f) / SCALE, (size.y / 2.f) / SCALE);
	_shape = new b2PolygonShape(sh);

	b2FixtureDef fixDef;
	fixDef.restitution = 1.f;
	fixDef.shape = _shape;
	_body->CreateFixture(&fixDef);

	sprite = Sprite::create("res/red.jpg", Rect(0, 0, size.x, size.y));
	sprite->setAnchorPoint(Vec2(0.5, 0.5));
	sprite->setPosition(position);

	//_body->SetLinearVelocity(b2Vec2(3, 0));
}

void DynamicObject::update(float dt) {
	auto pos = _body->GetPosition();

	//auto pos2 = _position;
	sprite->setPosition(Vec2(pos.x * SCALE, pos.y * SCALE));
	int debug2 = 0;
	//_position = Vec2(pos.x, pos.y);
}