#pragma once
#include "cocos2d.h"
#include "Box2D/Box2D.h"

USING_NS_CC;

class DynamicObject {
public:
	DynamicObject();

	DynamicObject(const cocos2d::Vec2& position, const cocos2d::Vec2& size);

	void update(float dt);

	cocos2d::Sprite* getSprite() const { return sprite; }

protected:
	b2Body* _body;
	b2Shape* _shape;

	cocos2d::Sprite* sprite;
};