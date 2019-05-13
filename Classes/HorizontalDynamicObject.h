#pragma once
#include "BehaviorDynamicObject.h"

class MoveDynamicObject : public BehaviorDynamicObject {
public:
	MoveDynamicObject();

	/*
	* сперва задаем сокрость, потом координаты
	*/
	void setBorders(const cocos2d::Vec2& leftPos, const cocos2d::Vec2& rightPos);

	virtual void update(float dt) override;
private:
	b2Vec2 _leftPosition;
	b2Vec2 _rightPosition;
	b2Vec2 _normalizeSpeed;
};