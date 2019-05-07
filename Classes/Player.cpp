#include "Player.h"

void Player::addBodyToWorld(std::shared_ptr<b2World> world)
{
	// let superclass to the work, we just need to set the player to be
	// a bullet so it doesn't fall through the world on huge updates
	Unit::addBodyToWorld(world);
	body->SetBullet(true);
}

void Player::addFixturesToBody()
{
	this->addCircularFixtureToBody(0.7f);
}