#pragma once
#include "PlatformerObject.h"
#include "BehaviorDynamicObject.h"

class DynamicObject : public PlatformerObject {
public:
	static DynamicObject* createObject();
	static DynamicObject* createObject(const std::string& fileName);
	static DynamicObject* createWithSpriteFrameName(const std::string& spriteFrameName);

	DynamicObject();

	virtual ~DynamicObject() {
		auto debug2 = 0;
	}

	virtual bool init(const cocos2d::Vec2& position, const cocos2d::Vec2& size);
	void initBehavior(const std::shared_ptr<BehaviorDynamicObject>& behavior);

	void update(float dt);
private:
	std::shared_ptr<BehaviorDynamicObject> _behavior;
};