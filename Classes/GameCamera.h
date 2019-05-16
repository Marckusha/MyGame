#pragma once
#include "cocos2d.h"
#include "Actor.h"

class GameCamera {
public:
	GameCamera(cocos2d::Camera* camera, std::shared_ptr<Actor> actor);

	GameCamera();

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event* event);

	void update(float dt);

private:
	cocos2d::Camera* _camera;
	std::shared_ptr<Actor> _actor;

	float _timer = 0.f;
	float _speedX = 0.f;
	float _speedY = 0.f;
	bool _isStart = true;
};
