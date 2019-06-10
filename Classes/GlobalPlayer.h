#pragma once
#include "cocos2d.h"

class GlobalPlayer : public cocos2d::Sprite {
public:
	GlobalPlayer();

	static GlobalPlayer* createPlayer();
	static GlobalPlayer* createPlayer(const std::string& fileName);
	static GlobalPlayer* createPlayerWithSpriteFrameName(const std::string& spriteFrameName);

	void initGraphWay(const std::vector< std::vector<std::pair<int, int>> >&);
	void initStartPostion(int startPosition);
	void initPositionLocation(const std::vector<cocos2d::Vec2>& pos);

	void update(float dt);

	void moveTo(int indexLocation);

	int getCurrentPoint() { return _point; }

private:
	void _initPath(int indexLocation);

private:
	std::vector< std::vector<std::pair<int, int>> > _graph;
	std::vector<int> _path;
	std::vector<cocos2d::Vec2> _positionLocation;

	int _startPosition = 0;
	int _point = -1;
	bool func = false;
};
