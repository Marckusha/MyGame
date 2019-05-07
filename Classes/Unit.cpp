#include "Unit.h"

USING_NS_CC;

void Unit::addBodyToWorld(std::shared_ptr<b2World> world) {
	// add a dynamic body to world
  // (subclasses can use other body types by overriding
  // this method and calling body->SetType())
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(
		this->getPositionX() / 32.f,
		this->getPositionY() / 32.f
	);
	bodyDef.userData = this;
	bodyDef.fixedRotation = true;
	this->body = world->CreateBody(&bodyDef);
}

void Unit::addCircularFixtureToBody(float radius)
{
	b2CircleShape shape;
	shape.m_radius = radius * this->getScale();
	this->createFixture(&shape);
}

void Unit::addRectangularFixtureToBody(float width, float height)
{
	b2PolygonShape shape;
	shape.SetAsBox(
		width * this->getScale(),
		height * this->getScale()
	);
	this->createFixture(&shape);
}



void Unit::createFixture(b2Shape* shape)
{
	// note that friction, etc. can be modified later by looping
	// over the body's fixtures and calling fixture->SetFriction()
	b2FixtureDef fixtureDef;
	fixtureDef.shape = shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.7f;
	fixtureDef.restitution = 0.1f;
	fixtureDef.filter.categoryBits = kFilterCategorySolidObject;
	fixtureDef.filter.maskBits = 0xffff;
	body->CreateFixture(&fixtureDef);
}

void Unit::setProperties(int x, int y)
{
	this->setPosition(Point(x, y));
}

void Unit::addSprite(const std::string& fileName) {
	//sprite = Sprite::create(fileName);
}