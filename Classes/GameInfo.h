#pragma once
#include "cocos2d.h"
#include "Box2D/Box2D.h"

class GameInfo {
public:
	static GameInfo& getInstance();

	void init();

	std::shared_ptr<b2World> getWorld() const { return _world; }

	int getExample() const { return _example; }
private:
	GameInfo();

	std::shared_ptr<b2World> _world;

	int _example = 0;
};