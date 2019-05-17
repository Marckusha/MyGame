#include "PeaceBehavior.h"

USING_NS_CC;

void PeaceBehavior::update(float dt) {
	if (_timer < _currentWay->first) {
		_timer += dt;
	}
	else if(!_isStart) {
		//to start unit
		if (_currentWay->second.x > _actor->getSprite()->getPositionX()) {
			_actor->moveToRight();
			_isLeft = false;
			_isRight = true;
		}
		else if (_currentWay->second.x < _actor->getSprite()->getPositionX()) {
			_actor->moveToLeft();
			_isLeft = true;
			_isRight = false;
		}
		
		_isStart = true;
	}

	if (_isRight && _currentWay->second.x < _actor->getSprite()->getPositionX()) {
		_isStart = false;
		_timer = 0.f;
		_actor->stop();
		_isLeft = false;
		_isRight = false;
		++_currentWay;
		if (_currentWay == _ways.end()) {
			_currentWay = _ways.begin();
		}
	}
	else if (_isLeft && _currentWay->second.x > _actor->getSprite()->getPositionX()) {
		_isStart = false;
		_timer = 0.f;
		_actor->stop();
		_isLeft = false;
		_isRight = false;
		++_currentWay;
		if (_currentWay == _ways.end()) {
			_currentWay = _ways.begin();
		}
	}
}