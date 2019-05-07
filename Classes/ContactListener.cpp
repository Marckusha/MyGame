#include "ContactListener.h"

USING_NS_CC;

ContactListener::ContactListener()
{}

ContactListener::ContactListener(std::shared_ptr<Actor> actor, Scene* scene) {
	_actor = actor;
	_gameScene = scene;
	_gameScene->retain();
}

void ContactListener::BeginContact(b2Contact* contact) {
	//_actor->countJumpNull();
}

void ContactListener::EndContact(b2Contact* contact) {}