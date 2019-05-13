#include "HorizontalDynamicObject.h"
#include "GameInfo.h"

USING_NS_CC;

MoveDynamicObject::MoveDynamicObject()
{}

void MoveDynamicObject::update(float dt) {

	if (_leftPosition.Length() - _body->GetPosition().Length() >= 0) {
		_body->SetLinearVelocity(_normalizeSpeed);
	}
	else if (_rightPosition.Length() - _body->GetPosition().Length() <= 0) {
		_body->SetLinearVelocity(-_normalizeSpeed);
	}
}

void MoveDynamicObject::setBorders(const Vec2& leftPos, const Vec2& rightPos) {

	auto SCALE = GameInfo::getInstance().getScaleWorld();

	auto left = leftPos / SCALE;
	auto right = rightPos / SCALE;
	auto normalize = (right - left).getNormalized();

	_leftPosition = b2Vec2(left.x, left.y);
	_rightPosition = b2Vec2(right.x, right.y);
	_normalizeSpeed = b2Vec2(normalize.x * _speed, normalize.y * _speed);
}