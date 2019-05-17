#pragma once
#include "ActorBehavior.h"

class PeaceBehavior : public ActorBehavior {
public:
	//first - time delay, second - coordinate
	typedef std::pair<float, cocos2d::Vec2> Way;

	PeaceBehavior()
	{	}

	explicit PeaceBehavior(std::shared_ptr<Actor> actor, const std::list<Way>& ways)
		: ActorBehavior(actor)
		, _ways(ways)
	{
		_currentWay = _ways.begin();
	}

	void addWays(const std::list<Way>& ways) {
		_ways = ways;
		_currentWay = _ways.begin();
	}

	virtual void update(float dt) override;

protected:
	std::list<Way> _ways;
	std::list<Way>::iterator _currentWay;

	//AI
	float _timer = 0.f;
	bool _isStart = false;
	bool _isLeft = false; 
	bool _isRight = false;
};
