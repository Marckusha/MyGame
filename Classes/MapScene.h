#pragma once
#include "cocos2d.h"
#include "Location.h"

class MapScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);

	void onMouseDown(cocos2d::Event* event);
	void onMouseMove(cocos2d::Event* event);

	CREATE_FUNC(MapScene);

private:
	bool _parsingRoutes(const std::string& fileName);
	void _initGraph(const std::vector< std::pair<std::string, std::string> >&);
	void _initPath(int positionTo);

private:
	cocos2d::Vector<Location*> _locations;
	std::vector< std::vector<std::pair<int, int>> > _graph;
	std::vector<int> _path;

	int _startPosition;


	cocos2d::Sprite* _character;
};
