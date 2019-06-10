#pragma once
#include "cocos2d.h"

class HealthPoint {
public:
	enum State { damage, healing };

	HealthPoint(cocos2d::Scene* scene);

	void update(State state);

	void setPosition(const cocos2d::Vec2& vect);

private:
	std::vector<cocos2d::Sprite*> _hp;

	const int MaxSizeHP = 3;

	int currentSizeHp = 3;
};