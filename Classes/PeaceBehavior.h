#pragma once
#include "ActorBehavior.h"

class PeaceBehavior : public ActorBehavior {
public:
	//first - time delay, second - coordinate
	typedef std::pair<float, cocos2d::Vec2> Way;

	PeaceBehavior() 	{}

	PeaceBehavior(const std::list<Way>& ways)
		: _ways(ways)
	{
		_currentWay = _ways.begin();
	}

	void addWays(const std::list<Way>& ways) {
		_ways = ways;
		_currentWay = _ways.begin();
	}

	virtual void update(float dt, Actor* actor) override;

	virtual void apply(std::shared_ptr<Player> player) override;

protected:
	std::list<Way> _ways;
	std::list<Way>::iterator _currentWay;

	//AI
	float _timer = 0.f;
	bool _isStart = false;
	bool _isLeft = false; 
	bool _isRight = false;
};
