#pragma once
#include "cocos2d.h"

class TestScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	bool init() override;

	void update(float dt) override;

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode, cocos2d::Event* event);

	CREATE_FUNC(TestScene);
private:
};