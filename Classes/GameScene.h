#pragma once
#include "cocos2d.h"
#include "Actor.h"
#include "StaticObject.h"
#include "DynamicObject.h"
#include "ContactListener.h"
#include "PlatformerObject.h"
#include "GameCamera.h"

//TODO
///Ïåðåïèñàòü âñþ ñöåíó

class GameScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init() override;

	void update(float dt) override;

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode, cocos2d::Event* event);

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event* event);

	CREATE_FUNC(GameScene);

private:
	void createRectangularFixture(cocos2d::TMXLayer* layer, int x, int y, float width, float height);

	void createFixtures(cocos2d::TMXLayer*);
	
private:
	std::shared_ptr<b2World> _world;
	std::shared_ptr<Actor> _actor;

	GameCamera _gameCamera;
	DynamicObject* _dyn;

	ContactListener _contList;
	std::vector<StaticObject> objects;
};