#pragma once
#include "cocos2d.h"

class Location : public cocos2d::Sprite {
public:
	Location();

	static Location* createLocation();
	static Location* createLocation(const std::string& fileName);
	static Location* createLocationWithSpriteFrameName(const std::string& spriteFrameName);

	void setNameTexture(const std::string& origin, const std::string& light);

	void select();
	void dontSelect();

private:
	bool _isSelect = false;

	std::string _originTexture = "";
	std::string _lightTexture = "";
};