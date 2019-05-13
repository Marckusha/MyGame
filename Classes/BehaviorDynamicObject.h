#pragma once
#include "cocos2d.h"
#include "Box2D/Box2D.h"

class BehaviorDynamicObject {
public:
	//TODO 
	///утечка памяти
	BehaviorDynamicObject()	{}

	void setSpeed(float speed) { _speed = speed; }

	//todo
	///memory
	void setBody(b2Body* body) { _body = body; }

	virtual void update(float dt) = 0;
protected:
	b2Body* _body;
	
	float _speed = 0.f;
};