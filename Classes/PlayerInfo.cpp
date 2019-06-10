#include "PlayerInfo.h"
#include "Player.h"

USING_NS_CC;

PlayerInfo& PlayerInfo::getInstance() {

	static PlayerInfo _instance;
	return _instance;
}

void PlayerInfo::init() {
	//parsing start info

	//TODO
	//init player

	//_player = std::shared_ptr<Player>(new Player());
}