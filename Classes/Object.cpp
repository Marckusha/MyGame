#include "Object.h"
#include "GameInfo.h"
#include "Player.h"

USING_NS_CC;

ObjectGame::ObjectGame(const std::string& nameFile, const cocos2d::Vec2& position, std::shared_ptr<b2World> world) {
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

	_sprite = Sprite::createWithSpriteFrameName(nameFile); 
	_sprite->setAnchorPoint(Vec2(0.5, 0.5));
	_sprite->setPosition(posX, posY);

	auto size = _sprite->getContentSize();

	//TODO
	///size sprite from XML
	float width = size.width / SCALE;
	float height = size.height / SCALE;

	b2PolygonShape sh;
	sh.SetAsBox(width / 2.f, height / 2.f);
	_shape = new b2PolygonShape(sh);

	b2FixtureDef fixDef;
	fixDef.density = 0.f;
	fixDef.friction = 1.f;
	fixDef.shape = _shape;
	_body->CreateFixture(&fixDef);

	/*_sprite = Sprite::create(FileNameInfo, Rect(0, 0, 133, 145));
	sprite->setAnchorPoint(Vec2(0.5, 0.5));
	sprite->setPosition(posX, posY);

	std::string nameAnim = _animationMap.at("idle");
	_setAnimation(nameAnim);*/
}

void ObjectGame::update(float dt) {
	auto SCALE = GameInfo::getInstance().getScaleWorld();
	auto pos = _body->GetPosition();
	_sprite->setPosition(Vec2(pos.x * SCALE, pos.y * SCALE));
}

void ObjectGame::apply(std::shared_ptr<Player> player) {

}

ObjectGame::~ObjectGame() {
	auto world = _body->GetWorld();
	delete _shape;
	if (!world->IsLocked()) {
		world->DestroyBody(_body);
	}
}