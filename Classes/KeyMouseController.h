#pragma once
#include "ControllerComponent.h"

class KeyMouseController : public ControllerComponent {
public:
	KeyMouseController();

	KeyMouseController(cocos2d::Sprite* sprite);

	virtual void attack();
};
