#pragma once
#include "cocos2d.h"
#include "Actor.h"
#include "StaticObject.h"
#include "DynamicObject.h"
#include "ContactListener.h"

class MainScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init() override;

	//Unit* addObject(std::string className, cocos2d::Vec2 pos);

	void update(float dt) override;

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode, cocos2d::Event* event);
	
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event* event);

	void updateCamera(float dt);

	CREATE_FUNC(MainScene);

private:
	void createRectangularFixture(cocos2d::TMXLayer* layer, int x, int y, float width, float height);

	void createFixtures(cocos2d::TMXLayer*);

	float speed = 0.f;
	float actorPosX = 0.f;
	float deltaActorPosX = 0.f;
	float speedActor = 0.f;
	float _timer = 0.f;
	bool _isStart = true;

	float speedActorY = 0.f;
	float speedY = 0.f;
	float actorPosY = 0.f;
	float deltaActorPosY = 0.f;
	float _timerY = 0.f;

	bool _buttonIsActive = false;

	std::shared_ptr<b2World> _world;


	std::shared_ptr<Actor> _actor;

	//Actor* actor;
	DynamicObject dyn;

	ContactListener _contList;

	std::vector<StaticObject> objects;
};