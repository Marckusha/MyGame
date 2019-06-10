#include "DamageBehavior.h"

USING_NS_CC;

void DamageBehavior::update(float dt, Actor* actor) {
	if (_timerDamage > 0) {
		_timerDamage -= dt;
		if (_timerDamage <= 0) {
			_damage = true;
		}
	}

	if (_timer < _currentWay->first) {
		_timer += dt;
	}
	else if (!_isStart) {
		//to start unit
		if (_currentWay->second.x > actor->getSprite()->getPositionX()) {
			actor->moveToRight();
			_isLeft = false;
			_isRight = true;
		}
		else if (_currentWay->second.x < actor->getSprite()->getPositionX()) {
			actor->moveToLeft();
			_isLeft = true;
			_isRight = false;
		}

		_isStart = true;
	}
	auto debug2 = 0;

	if (_isRight && _currentWay->second.x < actor->getSprite()->getPositionX()) {
		_isStart = false;
		_timer = 0.f;
		actor->stop();
		_isLeft = false;
		_isRight = false;
		++_currentWay;
		if (_currentWay == _ways.end()) {
			_currentWay = _ways.begin();
		}
	}
	else if (_isLeft && _currentWay->second.x > actor->getSprite()->getPositionX()) {
		_isStart = false;
		_timer = 0.f;
		actor->stop();
		_isLeft = false;
		_isRight = false;
		++_currentWay;
		if (_currentWay == _ways.end()) {
			_currentWay = _ways.begin();
		}
	}
}

void DamageBehavior::apply(std::shared_ptr<Player> player) {

	if (!_damage) {
		return;
	}
	_timerDamage = 1.f;
	_damage = false;

	auto contactList = player->getBody()->GetContactList();
	if (contactList != nullptr) {
		contactList->contact->SetFriction(20.f);
	}
	player->getBody()->SetLinearVelocity(b2Vec2(0.f, 0.f));

	float speed = 15.f;

	if (player->getSprite()->getRotationSkewY() == 0) {
		speed *= -1;
	}

	player->getBody()->ApplyLinearImpulseToCenter(b2Vec2(speed, 15), true);
	player->blockAllAction();
}