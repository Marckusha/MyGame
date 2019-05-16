#include "Actor.h"
#include "GameInfo.h"

USING_NS_CC;

auto SCALE = GameInfo::getInstance().getScaleWorld();

Actor::Actor() {
	auto world = GameInfo::getInstance().getWorld();

	//TODO
	///start position from XML
	float posX = 300;
	float posY = 300;

	b2BodyDef bodyDef;
	bodyDef.position.Set(posX / SCALE, posY / SCALE);
	bodyDef.type = b2_dynamicBody;
	_body = world->CreateBody(&bodyDef);


	//TODO
	///size sprite from XML
	float width = 133 / SCALE;
	float height = 145 / SCALE;

	b2PolygonShape sh;
	sh.SetAsBox(width / 2.f, height / 2.f);
	_shape = new b2PolygonShape(sh);

	b2FixtureDef fixDef;
	fixDef.density = 0.f;
	fixDef.friction = 0.f;
	fixDef.shape = _shape;
	_body->CreateFixture(&fixDef);

	sprite = Sprite::create("player.png", Rect(0, 0, 133, 145));
	sprite->setAnchorPoint(Vec2(0.5, 0.5));
	sprite->setPosition(posX, posY);

	_animationSet = AnimationSet::create("texturesConfig/config/animation.xml");
	_animationSet->retain();

	Animation* animation = _animationSet->getAnimation("idle");
	Animate* animate = Animate::create(animation);
	RepeatForever* action = RepeatForever::create(animate);
	sprite->runAction(action);
}

void Actor::update(float dt) {
	auto pos = _body->GetPosition();
	sprite->setPosition(Vec2(pos.x * SCALE, pos.y * SCALE));

	if (_body->GetLinearVelocity().y != 0) {
		_state = jump;
	}
	else {
		_state = notjump;
		_countJump = 0;
	}

	//velocity
	_dtPosition.x = std::abs(_prevPosition.x - sprite->getPositionX());
	_dtPosition.y = std::abs(_prevPosition.y - sprite->getPositionY());

	_prevPosition.x = sprite->getPositionX();
	_prevPosition.y = sprite->getPositionY();

	if (dt != 0) {
		_speedActor.x = _dtPosition.x / dt;
		_speedActor.y = _dtPosition.y / dt;
	}
}

void Actor::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {

	//TODO
	///from XML
	float inmpulse = 1000 / 2.f;

	auto getAnimation = [=](const std::string& nameAnim) {
		auto cacher = AnimationCache::getInstance();

		Animation* animation = cacher->getAnimation(nameAnim);
		Animate* animate = Animate::create(animation);
		RepeatForever* action = RepeatForever::create(animate);
		sprite->runAction(action);
	};

	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {

		sprite->stopAllActions();

		auto contList = _body->GetContactList();
		if (contList) {
			contList->contact->SetFriction(0.f);
		}
		//

		//TODO
		///from XML
		getAnimation("run");

		_body->SetLinearVelocity(b2Vec2(-15, 0));
		sprite->setRotationSkewY(180);
		_countRun++;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {

		sprite->stopAllActions();
		//TODO
		///from XML
		//_body->GetFixtureList()->SetFriction(0.f);

		auto contList = _body->GetContactList();
		if (contList) {
			contList->contact->SetFriction(0.f);
		}
		//

		getAnimation("run");

		_body->SetLinearVelocity(b2Vec2(15, 0));
		sprite->setRotationSkewY(0);
		_countRun++;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW && _countJump < 2) {
		_body->ApplyForceToCenter(b2Vec2(0, inmpulse * 2), true);
		++_countJump;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_Q) {
	}
}

void Actor::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {

	auto getAnimation = [=](const std::string& nameAnim) {
		auto cacher = AnimationCache::getInstance();

		Animation* animation = cacher->getAnimation(nameAnim);
		Animate* animate = Animate::create(animation);
		RepeatForever* action = RepeatForever::create(animate);
		sprite->runAction(action);
	};

	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {

		_countRun--;

		//from friction on dynamic blocks
		if (_countRun == 0) {
			sprite->stopAllActions();
			//TODO
			///from XML
			getAnimation("idle");

			auto contList = _body->GetContactList();
			if (contList) {
				contList->contact->SetFriction(1.f);
				contList->contact->SetEnabled(false);
			}

			_body->SetLinearVelocity(b2Vec2(0, 0));
			sprite->setRotationSkewY(180);
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		_countRun--;
		if (_countRun == 0) {

			//TODO
			///from XML
			sprite->stopAllActions();
			getAnimation("idle");
			
			auto contList = _body->GetContactList();
			if (contList) {
				contList->contact->SetFriction(1.f);
				contList->contact->SetEnabled(false);
			}
			//_body->GetContactList()->contact->SetFriction(1.f);

			_body->SetLinearVelocity(b2Vec2(0, 0));
			sprite->setRotationSkewY(0);
		}
	}
}

/*bool Actor::isMoving() const {
	if (_body->GetLinearVelocity().x > 0 || _body->GetLinearVelocity().y > 0) {
		return true;
	}
	else {
		return false;
	}
}*/