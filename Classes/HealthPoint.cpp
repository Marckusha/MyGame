#include "HealthPoint.h"

USING_NS_CC;

HealthPoint::HealthPoint(Scene* scene) {

	for (int i = 0; i < MaxSizeHP; ++i) {
		Sprite* sprite = Sprite::createWithSpriteFrameName("hp.png");
		sprite->setAnchorPoint(Vec2(0.5, 0.5));
		float x = sprite->getContentSize().width / 2.f + sprite->getContentSize().width * i;
		float y = 768.f - sprite->getContentSize().height / 2.f;
		sprite->setPosition(x, y);
		_hp.push_back(sprite);
		scene->addChild(sprite);
	}
}

void HealthPoint::setPosition(const Vec2& vect) {
	for (int i = 0; i < _hp.size(); ++i) {
		float x = _hp[i]->getContentSize().width / 2.f + _hp[i]->getContentSize().width * i + vect.x - 1024 / 2.f;
		float y = vect.y + 768 / 2.f - _hp[i]->getContentSize().height / 2.f;
		_hp[i]->setPosition(x, y);
	}
}

void HealthPoint::update(State state) {
	if (state == State::damage && currentSizeHp > 0) {
		_hp[currentSizeHp - 1]->setVisible(false);
		--currentSizeHp;
	}
}
