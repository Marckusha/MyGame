#include "BaseActor.h"
#include "GameInfo.h"

USING_NS_CC;

/*BaseActor::BaseActor() {
	this->init();
}*/

BaseActor::BaseActor(const AnimationMap& animMap, const Vec2& position, std::shared_ptr<b2World> world)
	: _animationMap(animMap)
{
	//auto world = GameInfo::getInstance().getWorld();
	auto SCALE = GameInfo::getInstance().getScaleWorld();

	//TODO
	///start position from XML
	float posX = position.x;
	float posY = position.y;

	b2BodyDef bodyDef;
	bodyDef.position.Set(posX / SCALE, posY / SCALE);
	bodyDef.type = b2_dynamicBody;
	_body = world->CreateBody(&bodyDef);

	//TODO
	///size sprite from XML
	float width = 133 / SCALE;
	float height = 145 / SCALE;

	b2PolygonShape sh;
	sh.SetAsBox(width / 2.f, height / 2.f);
	_shape = new b2PolygonShape(sh);

	b2FixtureDef fixDef;
	fixDef.density = 0.f;
	fixDef.friction = 0.f;
	fixDef.shape = _shape;
	_body->CreateFixture(&fixDef);

	sprite = Sprite::create("player.png", Rect(0, 0, 133, 145));
	sprite->setAnchorPoint(Vec2(0.5, 0.5));
	sprite->setPosition(posX, posY);

	std::string nameAnim = _animationMap.at("idle");
	_setAnimation(nameAnim);
}

void BaseActor::update(float dt) {
	auto SCALE = GameInfo::getInstance().getScaleWorld();
	auto pos = _body->GetPosition();
	sprite->setPosition(Vec2(pos.x * SCALE, pos.y * SCALE));
}

BaseActor::~BaseActor() {
	auto world = _body->GetWorld();
	delete _shape;
	if (!world->IsLocked()) {
		world->DestroyBody(_body);
	}
}

void BaseActor::_setAnimation(const std::string& nameAnim) {
	auto cacher = AnimationCache::getInstance();

	Animation* animation = cacher->getAnimation(nameAnim);
	Animate* animate = Animate::create(animation);
	RepeatForever* action = RepeatForever::create(animate);
	sprite->runAction(action);
}