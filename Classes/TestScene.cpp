#include "TestScene.h"

USING_NS_CC;

Scene* TestScene::createScene() {
	auto scene = TestScene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	return scene;
}

bool TestScene::init() {

	if (!Scene::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2((visibleSize.width / 2.f + origin.x), (visibleSize.height / 2.f + origin.y)));
	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode);

	return true;
}

void TestScene::update(float dt) {

}

void TestScene::onKeyPressed(EventKeyboard::KeyCode, Event* event) {

}