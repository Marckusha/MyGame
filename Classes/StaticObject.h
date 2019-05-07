#pragma once
#include "cocos2d.h"
#include "Box2D/Box2D.h"

class StaticObject {
public:
	StaticObject();

	StaticObject(const cocos2d::Vec2& position, const cocos2d::Vec2& size);

	cocos2d::Sprite* getSprite() const { return sprite; }

protected:
	b2Body* _body;
	b2Shape* _shape;

	cocos2d::Sprite* sprite;
};