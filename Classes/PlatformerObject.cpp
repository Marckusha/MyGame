#include "PlatformerObject.h"
#include "GameInfo.h"

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

PlatformerObject::~PlatformerObject() {
	auto world = _body->GetWorld();
	delete _shape;
	if (!world->IsLocked()) {
		world->DestroyBody(_body);
	}

	if (_body2 == nullptr) {
		return;
	}
	auto world2 = _body2->GetWorld();
	if (!world2->IsLocked()) {
		world2->DestroyBody(_body2);
	}
}