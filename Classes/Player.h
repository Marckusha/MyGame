#pragma once
#include "Unit.h"

class Player : public Unit {
public:
	Player(){}

	void addBodyToWorld(std::shared_ptr<b2World> world);
	void addFixturesToBody();

	virtual ~Player() {}
};