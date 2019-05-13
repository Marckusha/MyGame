#pragma once
#include "cocos2d.h"
#include "Box2D/Box2D.h"

class PlatformerObject : public cocos2d::Sprite {
public:
	/*static PlatformerObject* createObject();
	static PlatformerObject* createObject(const std::string& fileName);
	static PlatformerObject* createWithSpriteFrameName(const std::string& spriteFrameName);*/

	PlatformerObject();

	virtual bool init(const cocos2d::Vec2& position, const cocos2d::Vec2& size);

	void setDebug(bool select);

	//TODO
	///не отображать и отключать, если объект находится вне видимости камеры

protected:
	b2Body* _body;
	b2Shape* _shape;
};
