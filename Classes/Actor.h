#pragma once
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "AnimationSet.h"

class Actor /*: public cocos2d::Sprite*/ {
public:

	enum State{jump, notjump};

	Actor();

	cocos2d::Sprite* getSprite() const { return sprite; }

	void countJumpNull() { _countJump = 0; }

	float getVelY() { return _body->GetLinearVelocity().x; }

	void update(float dt);

	bool isMoving() const;

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event* event);

protected:
	b2Body* _body;
	b2Shape* _shape;

	int _countJump = 0;

	cocos2d::Sprite* sprite;

	State _state = notjump;

	AnimationSet* _animationSet;
};
