#include "GameInfo.h"

GameInfo& GameInfo::getInstance() {

	static GameInfo _instance;
	return _instance;
}

GameInfo::GameInfo() {
	const float kPixelsPerMeter = 32.f;
	const float kGravity = -kPixelsPerMeter / 0.7f;

	_world = std::shared_ptr<b2World>(new b2World(b2Vec2(0.f, kGravity)));
	_worldForNPC = std::shared_ptr<b2World>(new b2World(b2Vec2(0.f, kGravity)));
}

void GameInfo::init() {

	const float kPixelsPerMeter = 32.f;
	const float kGravity = -kPixelsPerMeter / 0.7f;

	_world = std::shared_ptr<b2World>(new b2World(b2Vec2(0.f, kGravity)));
}

void GameInfo::destroy() {

	if (!_world->IsLocked()) {
		_world->~b2World();
	}
}