#pragma once
#include "Player.h"

class ContactListener : public b2ContactListener {
public:
	ContactListener();
	ContactListener(std::shared_ptr<Player> player, cocos2d::Scene* scene);

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);

private:
	std::shared_ptr<Player> _player;
	cocos2d::Scene* _gameScene;
};
