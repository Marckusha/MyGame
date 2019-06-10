#pragma once
#include "PlatformerObject.h"

class StaticObject : public PlatformerObject {
public:
	static StaticObject* createObject();
	static StaticObject* createObject(const std::string& fileName);
	static StaticObject* createWithSpriteFrameName(const std::string& spriteFrameName);

	StaticObject();

	virtual ~StaticObject();

	virtual bool init(const cocos2d::Vec2& position, const cocos2d::Vec2& size);
};