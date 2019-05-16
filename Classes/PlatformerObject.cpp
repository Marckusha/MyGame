#include "PlatformerObject.h"

USING_NS_CC;

PlatformerObject::PlatformerObject() {}

bool PlatformerObject::init(const Vec2& position, const Vec2& size) {

	this->setTextureRect(Rect(0, 0, size.x, size.y));
	this->setAnchorPoint(Vec2(0.5, 0.5));
	this->setPosition(position);

	return true;
}

void PlatformerObject::setDebug(bool select) {
	this->setVisible(select);
}