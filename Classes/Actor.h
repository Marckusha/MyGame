#pragma once
//#include "BaseActor.h"
#include "Player.h"

class ActorBehavior;

class Actor : public BaseActor {
public:
	Actor::Actor(const AnimationMap& animMap, const cocos2d::Vec2& position, std::shared_ptr<b2World> world);

	void setBehavior(std::shared_ptr<ActorBehavior> behavior) {
		_behavior = behavior;
	}

	std::shared_ptr<ActorBehavior> getBehavior() const { return _behavior; }

	virtual void update(float dt) override;

	virtual void apply(std::shared_ptr<Player> player);

	void moveToLeft();
	void moveToRight();
	void stop();

	void setSpeed(const cocos2d::Vec2& speed) {
		_speed = speed;
	}

	virtual ~Actor();

protected:
	std::shared_ptr<ActorBehavior> _behavior;

	/*int _countJump = 0;
	int _countRun = 0;
	State _state = notjump;

	//speed
	cocos2d::Vec2 _speedActor;
	cocos2d::Vec2 _dtPosition;
	cocos2d::Vec2 _prevPosition;*/
};
