#pragma once
#include "ActorBehavior.h"

class DamageBehavior : public ActorBehavior {
public:
	typedef std::pair<float, cocos2d::Vec2> Way;

	DamageBehavior()
	{	}

	DamageBehavior(const std::list<Way>& ways)
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

	bool getActiveDamage() const { return _damage; }

protected:
	std::list<Way> _ways;
	std::list<Way>::iterator _currentWay;

	bool _damage = true;
	float _timerDamage = 0.f;

	//AI
	float _timer = 0.f;
	bool _isStart = false;
	bool _isLeft = false;
	bool _isRight = false;
};