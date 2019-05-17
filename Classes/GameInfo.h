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
	std::shared_ptr<b2World> getWorldForNPC() const { return _worldForNPC; }

	float getScaleWorld() const { return _scaleWorld; } 
private:
	GameInfo();

	std::shared_ptr<b2World> _world;
	std::shared_ptr<b2World> _worldForNPC;

	const float _scaleWorld = 30.f;
};