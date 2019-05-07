#include "Actor.h"
#include "GameInfo.h"
#include "Box2D/Box2D.h"

USING_NS_CC;

const float SCALE = 30.f;

Actor::Actor() {
	auto world = GameInfo::getInstance().getWorld();

	float posX = 300;
	float posY = 300;

	b2BodyDef bodyDef;
	bodyDef.position.Set(posX/ SCALE, posY / SCALE);
	bodyDef.type = b2_dynamicBody;
	_body = world->CreateBody(&bodyDef);

	float width = 133 / SCALE;
	float height = 145 / SCALE;

	b2PolygonShape sh;
	sh.SetAsBox(width / 2.f, height / 2.f);
	_shape = new b2PolygonShape(sh);

	b2FixtureDef fixDef;
	fixDef.density = 0.f;
	fixDef.restitution = 0.f;
	fixDef.friction = 0.f;
	fixDef.shape = _shape;
	_body->CreateFixture(&fixDef);

	sprite = Sprite::create("player.png", Rect(0, 0, 133, 145));
	sprite->setAnchorPoint(Vec2(0.5, 0.5));
	sprite->setPosition(posX, posY);

	_animationSet = AnimationSet::create("texturesConfig/config/animation.xml");
	_animationSet->retain();

	Animation* _animation = _animationSet->getAnimation("run");
	Animate* animate = Animate::create(_animation);
	RepeatForever* action = RepeatForever::create(animate);
	sprite->runAction(action);

	//this->setPosition(posX, posY);
	//this->initWithFile("res/horse.png");
}

void Actor::update(float dt) {
	auto pos = _body->GetPosition();
	//auto pos2 = _position;
	sprite->setPosition(Vec2(pos.x * SCALE, pos.y * SCALE));
	int debug2 = 0;
	if (_body->GetLinearVelocity().y != 0) {
		_state = jump;
	}
	else {
		_state = notjump;
		_countJump = 0;
	}
	//_position = Vec2(pos.x, pos.y);
}

void Actor::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {

	float inmpulse = 1000 / 2.f;

	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		_body->SetLinearVelocity(b2Vec2(-15, 0));
		sprite->setRotationSkewY(180);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		_body->SetLinearVelocity(b2Vec2(15, 0));
		sprite->setRotationSkewY(0);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW && _countJump < 2) {
		//_body->SetLinearVelocity(b2Vec2(0, 10));
		_body->ApplyForceToCenter(b2Vec2(0, inmpulse * 2), true);
		++_countJump;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_Q) {

		//_body->ApplyLinearImpulse(b2Vec2(15, 0), b2Vec2(0.5, 0.5), true);
		//_body->ApplyForce(b2Vec2(15, 0), b2Vec2(0.5, 0.5), true);
		//_body->
	}
}

void Actor::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		_body->SetLinearVelocity(b2Vec2(0, 0));
		//_body->ApplyForceToCenter(b2Vec2(-10, 0), true);
		

		sprite->setRotationSkewY(180);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		_body->SetLinearVelocity(b2Vec2(0, 0));
		auto linerVel = _body->GetLinearVelocity();
		auto massa = _body->GetMass();
		sprite->setRotationSkewY(0);
	}
}

bool Actor::isMoving() const {
	if (_body->GetLinearVelocity().x > 0 || _body->GetLinearVelocity().y > 0) {
		return true;
	}
	else {
		return false;
	}
}