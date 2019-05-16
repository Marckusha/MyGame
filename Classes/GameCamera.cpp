#include "GameCamera.h"

USING_NS_CC;

GameCamera::GameCamera() 
	: _camera(nullptr)
{}

GameCamera::GameCamera(Camera* camera, std::shared_ptr<Actor> actor)
	: _camera(camera)
	, _actor(actor)
{}

//TODO
///refactoring
void GameCamera::update(float dt) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto scene = Director::getInstance()->getRunningScene();
	auto map = dynamic_cast<TMXTiledMap*>(scene->getChildByName("map"));

	if (_timer > 0) {

		float delta = 0.5f / dt;
		float value = _speedX / delta;

		_speedX -= value;
		_timer -= dt;

		if (_timer <= 0) {
			_speedX = 0;
		}
	}

	/*if (_actor->getVelocity().x == 0.f && _isStart) {
		_isStart = false;
		_timer = 0.7f;
		_speedX /= 2.f;
	}*/

	float camPos = _camera->getPositionX() + dt * _speedX;
	_camera->setPositionX(camPos);

	if (_camera->getPositionX() - _actor->getSprite()->getPositionX() > 100.f) {
		_speedX = -_actor->getVelocity().x;
		_isStart = true;
	}

	if (_actor->getSprite()->getPositionX() - _camera->getPositionX() > 100.f) {
		_speedX = _actor->getVelocity().x;
		_isStart = true;
	}

	if (_camera->getPosition().x < visibleSize.width / (2.f)) {
		_camera->setPositionX(visibleSize.width / (2.f));
	}
	else if (_camera->getPositionX() > map->getMapSize().width * map->getTileSize().width - (visibleSize.width / (2.f)))
	{
		_camera->setPositionX(map->getMapSize().width * map->getTileSize().width
			- (visibleSize.width / (2.f)));
	}


	float camPosY = _camera->getPositionY() + dt * _speedY;
	_camera->getDefaultCamera()->setPositionY(camPosY);

	if (_camera->getPositionY() - _actor->getSprite()->getPositionY() > 50.f) {
		_speedY = -250;
	}
	else if (_actor->getSprite()->getPositionY() - _camera->getPositionY() > 50.f) {
		_speedY = 70;
	}
	else {
		_speedY = 0.f;
	}

	if (_camera->getPositionY() < visibleSize.height / 2.f) {
		_camera->setPositionY(visibleSize.height / 2.f);
	}
}


void GameCamera::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW ||
		keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW && _isStart)
	{
		_isStart = false;
		_timer = 0.5f;
		_speedX /= 2.f;
	}
}