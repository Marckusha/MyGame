#pragma once
#include "cocos2d.h"
#include "Box2D/Box2D.h"

class PlatformerObject : public cocos2d::Sprite {
public:

	PlatformerObject();

	virtual bool init(const cocos2d::Vec2& position, const cocos2d::Vec2& size);

	void setDebug(bool select);

	virtual ~PlatformerObject();

	//TODO
	///�� ���������� � ���������, ���� ������ ��������� ��� ��������� ������

protected:
	b2Body* _body;
	b2Body* _body2;
	b2Shape* _shape;
};
