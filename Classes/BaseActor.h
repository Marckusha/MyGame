#pragma once
#include "cocos2d.h"
#include "Box2D/Box2D.h"

class BaseActor {
public:
	typedef std::map<std::string, std::string> AnimationMap;
	typedef std::pair<std::string, std::string> AnimationPair;

	//BaseActor();
	BaseActor(const AnimationMap& animMap, const cocos2d::Vec2& position, std::shared_ptr<b2World> world);

	//virtual void init();
	virtual void update(float dt);

	cocos2d::Sprite* getSprite() const { return sprite; }
	cocos2d::Vec2 getVelocity() const { return _speed; }
	b2Body* getBody() const { return _body; }

	virtual ~BaseActor();

protected:
	void _setAnimation(const std::string& nameAnim);

protected:
	b2Body* _body;
	b2Shape* _shape;
	cocos2d::Sprite* sprite;
	AnimationMap _animationMap;

	cocos2d::Vec2 _speed;

	/*int _countJump = 0;
	int _countRun = 0;
	State _state = notjump;

	//speed
	cocos2d::Vec2 _speedActor;
	cocos2d::Vec2 _dtPosition;
	cocos2d::Vec2 _prevPosition;*/

};
