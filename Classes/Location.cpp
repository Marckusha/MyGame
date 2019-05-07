#include "Location.h"

USING_NS_CC;

Location::Location() 
	:Sprite()
{}

Location* Location::createBox() {
	Location* location = new Location();
	location->autorelease();
	return location;
}

Location* Location::createBox(const std::string& fileName) {
	Location* location = new Location();
	location->initWithFile(fileName);
	location->autorelease();
	return location;
}

Location* Location::createBoxWithSpriteFrameName(const std::string& spriteFrameName) {
	Location* location = new Location();
	location->initWithSpriteFrameName(spriteFrameName);
	location->autorelease();
	return location;
}