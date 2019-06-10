#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "StaticObject.h"
#include "DynamicObject.h"
#include "ContactListener.h"
#include "PlatformerObject.h"
#include "GameCamera.h"
#include "Actor.h"
#include "BaseActor.h"
#include "HealthPoint.h"
//#include "Object.h"

//TODO
///Ïåðåïèñàòü âñþ ñöåíó

class GameScene : public cocos2d::Scene {
public:

	GameScene() {}

	GameScene(const std::string& str) { _fileName = str; }

	static cocos2d::Scene* createScene(const std::string& str);

	virtual bool init() override;

	void update(float dt) override;

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode, cocos2d::Event* event);

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event* event);

	CREATE_FUNC(GameScene);

private:
	//void createRectangularFixture(cocos2d::TMXLayer* layer, int x, int y, float width, float height);

	void createFixtures(cocos2d::TMXLayer*);

	void createActors(cocos2d::TMXObjectGroup*);

	void createKinematicObject(cocos2d::TMXObjectGroup*);

	//void _initObjects();
	
private:
	std::shared_ptr<b2World> _world;
	std::shared_ptr<b2World> _worldForNPC;

	std::shared_ptr<Player> _player; 
	std::vector< std::shared_ptr<Actor> > _actors;
	std::vector<DynamicObject*> _dynamicObjects;
	std::vector<StaticObject> objects;

	std::shared_ptr<HealthPoint> _healthPoint;

	//std::vector< std::shared_ptr<ObjectGame> > _objects;

	GameCamera _gameCamera;
	//DynamicObject* _dyn;

	ContactListener _contList;

	//TODO chevo-to
	std::string _fileName = "";

	bool _isPause = false;
};