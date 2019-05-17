#include "Player.h"
#include "GameInfo.h"

USING_NS_CC;

auto SCALE = GameInfo::getInstance().getScaleWorld();

Player::Player(const AnimationMap& animMap, const Vec2& position, std::shared_ptr<b2World> world)
	: BaseActor(animMap, position, world)
{}

void Player::update(float dt) {
	BaseActor::update(dt);

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
		_speed.x = _dtPosition.x / dt;
		_speed.y = _dtPosition.y / dt;
	}
}

void Player::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {

	//TODO
	///from XML
	float inmpulse = 1000 / 2.f;

	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {

		sprite->stopAllActions();

		auto contList = _body->GetContactList();
		if (contList) {
			contList->contact->SetFriction(0.f);
		}
		//

		//TODO
		///from XML
		_setAnimation("run");

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

		_setAnimation("run");

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

void Player::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {

	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {

		_countRun--;

		//from friction on dynamic blocks
		if (_countRun == 0) {
			sprite->stopAllActions();
			//TODO
			///from XML
			_setAnimation("idle");

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
			_setAnimation("idle");

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