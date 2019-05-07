#include "StartScene.h"
#include "MainMenu.h"

USING_NS_CC;

Scene* StartScene::createScene() {
	return StartScene::create();
}

bool StartScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto director = Director::getInstance();
	auto visibleSize = director->getVisibleSize();

	auto mainLable = Label::create("Marckush Project", "arial.ttf", 100);
	mainLable->setColor(Color3B::WHITE);
	mainLable->setPosition(Vec2(visibleSize.width / 2.f, visibleSize.height / 2.f));
	this->addChild(mainLable);

	this->scheduleUpdate();

	return true;
}

void StartScene::update(float dt) {
	_timer += dt;

	float delayScene = 1;

	if (_timer > delayScene) {
		Scene* scene = MainMenu::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 255, 255)));
	}
}