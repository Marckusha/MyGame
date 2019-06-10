#pragma once
#include "BaseActor.h"

class Player : public BaseActor {
public:
	enum State { jump, notjump };

	Player(const AnimationMap& animMap, const cocos2d::Vec2& position, std::shared_ptr<b2World> world);

	virtual void update(float dt) override;

	void blockAllAction();
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event* event);

	virtual ~Player() { auto debug2 = 0; }

protected:
	int _countJump = 0;
	int _countRun = 0;
	State _state = notjump;

	bool _isAction = true;

	//speed
	cocos2d::Vec2 _dtPosition;
	cocos2d::Vec2 _prevPosition;
};