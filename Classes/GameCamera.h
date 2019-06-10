#pragma once
#include "cocos2d.h"
#include "Player.h"

class GameCamera {
public:
	GameCamera(cocos2d::Camera* camera, std::shared_ptr<Player> _player);

	GameCamera();

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event* event);

	void update(float dt);

	cocos2d::Vec2 getPosition() const { return _camera->getPosition(); }

private:
	cocos2d::Camera* _camera;
	std::shared_ptr<Player> _player;

	float _timer = 0.f;
	float _speedX = 0.f;
	float _speedY = 0.f;
	bool _isStart = true;
};
