#pragma once
#include "cocos2d.h"

class ControllerComponent {
public:
	ControllerComponent();

	ControllerComponent(cocos2d::Sprite*);

	virtual void attack() = 0;

protected:
	cocos2d::Sprite* _controllSprite;
};