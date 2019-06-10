#pragma once
#include "cocos2d.h"

class Player;
class ObjectGame;

class PlayerInfo {
public:
	static PlayerInfo& getInstance();

	std::shared_ptr<Player> getPlayer() const { return _player; }

	void init();

	void pushBack(std::shared_ptr<ObjectGame> obj) {
		_objects.push_back(obj);
	}
	
	//TODO
	///write func erase
	//void erase(std::shared_ptr<ObjectGame> obj);

	//TODO
	///write this function (parsing save file)
	//void initFromFile(const std::string& fileName);

private:
	PlayerInfo() {}

	//skills
	//quest

	std::shared_ptr<Player> _player;
	std::vector< std::shared_ptr<ObjectGame> > _objects;
};