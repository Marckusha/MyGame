#pragma once
#include "cocos2d.h"

struct NPCInfo {
	std::list< std::pair<float, cocos2d::Vec2> > ways;

	std::string typeActor = "";

	cocos2d::Vec2 startPosition = cocos2d::Vec2();

	cocos2d::Vec2 speed = cocos2d::Vec2();

	std::map<std::string, std::string> animationMap;
	//etc
};
