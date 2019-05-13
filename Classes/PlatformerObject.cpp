#include "PlatformerObject.h"

USING_NS_CC;

PlatformerObject::PlatformerObject() {}

/*PlatformerObject* PlatformerObject::createObject() {
	PlatformerObject* platformetObject = new PlatformerObject();
	platformetObject->autorelease();
	return platformetObject;
}

PlatformerObject* PlatformerObject::createObject(const std::string& fileName) {
	PlatformerObject* platformetObject = new PlatformerObject();
	platformetObject->initWithFile(fileName);
	platformetObject->autorelease();
	return platformetObject;
}

PlatformerObject* PlatformerObject::createWithSpriteFrameName(const std::string& spriteFrameName) {
	PlatformerObject* platformetObject = new PlatformerObject();
	platformetObject->initWithSpriteFrameName(spriteFrameName);
	platformetObject->autorelease();
	return platformetObject;
}*/

bool PlatformerObject::init(const Vec2& position, const Vec2& size) {

	this->setTextureRect(Rect(0, 0, size.x, size.y));
	this->setAnchorPoint(Vec2(0.5, 0.5));
	this->setPosition(position);

	return true;
}

void PlatformerObject::setDebug(bool select) {
	this->setVisible(select);
}