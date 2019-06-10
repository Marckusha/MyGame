#pragma once
#include "cocos2d.h"
#include "Box2D/Box2D.h"

class Player;

class ObjectGame {
public:
	typedef std::map<std::string, std::string> AnimationMap;
	typedef std::pair<std::string, std::string> AnimationPair;

	//BaseActor();
	ObjectGame(const std::string& nameFile, const cocos2d::Vec2& position, std::shared_ptr<b2World> world);

	//virtual void init();
	virtual void update(float dt);
	virtual void apply(std::shared_ptr<Player> player);

	cocos2d::Sprite* getSprite() const { return _sprite; }
	b2Body* getBody() const { return _body; }

	virtual ~ObjectGame();

protected:
	b2Body* _body;
	b2Shape* _shape;
	cocos2d::Sprite* _sprite;

	std::string _textureNameFromWorld = "";
	std::string _textureNameFromInterface = "";
};
