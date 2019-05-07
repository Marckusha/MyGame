#pragma once
#include "cocos2d.h"
#include "Box2D/Box2D.h"

class Unit : public cocos2d::Sprite {
public:

	/*static Unit* createSprite(const std::string& filaName) {

		return new 
		//return Unit::create(filaName);
	}*/

	enum
	{
		kFilterCategoryLevel = 0x01,
		kFilterCategorySolidObject = 0x02,
		kFilterCategoryNonSolidObject = 0x04
	};

	Unit(){}

	void addBodyToWorld(std::shared_ptr<b2World> world);
	void createFixture(b2Shape* shape);
	void addRectangularFixtureToBody(float width, float height);
	void addCircularFixtureToBody(float radius);
	void setProperties(int x, int y);
	void addSprite(const std::string& fileName);

	virtual ~Unit() {}

protected:
	b2Body* body;
};