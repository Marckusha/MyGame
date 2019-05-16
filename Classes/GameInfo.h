#pragma once
//#include "cocos2d.h"
#include "Box2D/Box2D.h"

/** @class GameInfo
* @brief Синглтон;отображает информацию о мире 
*/
class GameInfo {
public:
	static GameInfo& getInstance();

	void init();

	std::shared_ptr<b2World> getWorld() const { return _world; }

	float getScaleWorld() const { return _scaleWorld; } 

	//int getExample() const { return _example; }
private:
	GameInfo();

	std::shared_ptr<b2World> _world;

	const float _scaleWorld = 30.f;
};