#include "MainMenu.h"
#include "MapScene.h"

USING_NS_CC;

Scene* MainMenu::createScene() {
	return MainMenu::create();
}

bool MainMenu::init() {

	if (!Scene::init()) {
		return false;
	}

	//TODO
	///Парсинг файла локализации
	///Проверка на предыдущее сохранение
	_playText = "Play";
	_exitText = "Exit";
	_continueText = "Continue";
	_langText = "Language";
	_backText = "Back";

	//TODO
	///после парсинга получаем путь до нужных файлов
	std::string pathBackground = "texturesConfig/interface/mainMenu/background.jpg";
	std::string pathFontName = "fonts/kirillStyle.otf";

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/// add background
	auto sprite = Sprite::create(pathBackground);
	sprite->setAnchorPoint(Vec2(0, 0.5));
	sprite->setPosition(Vec2(0, visibleSize.height / 2));
	sprite->setScale(visibleSize.width / sprite->getContentSize().width);
	this->addChild(sprite, 0);

	/// add mainMenu
	Menu* mainMenu = Menu::create();
	mainMenu->setPosition(Vec2::ZERO);
	this->addChild(mainMenu);

	std::string fontName(pathFontName);

	///add continue button
	if (!_isNew) {
		Label* cont = Label::createWithTTF(_continueText, fontName, 46);

		MenuItemLabel* contButton = MenuItemLabel::create(cont);
		contButton->setPosition(150, 350);
		contButton->setCallback([&](Ref* sender) {
			//TODO
			///load save
			///replace scene
		});
		mainMenu->addChild(contButton);
	}

	/// add play button
	Label* play = Label::createWithTTF(_playText, fontName, 46);

	MenuItemLabel* playButton = MenuItemLabel::create(play);
	playButton->setPosition(150, 300);
	playButton->setCallback([&](cocos2d::Ref *sender) {
		Director::getInstance()->replaceScene(MapScene::createScene());
	});
	mainMenu->addChild(playButton);

	///add language button
	Label* lang = Label::createWithTTF(_langText, fontName, 46);

	MenuItemLabel* langButton = MenuItemLabel::create(lang);
	langButton->setPosition(150, 250);
	langButton->setCallback([&](Ref* sender) {
		//TODO
		///replace lang
	});
	mainMenu->addChild(langButton);

	/// add exit button
	Label* exit = Label::createWithTTF(_exitText, fontName, 36);
	MenuItemLabel* exitButton = MenuItemLabel::create(exit);
	exitButton->setPosition(150, 200);
	exitButton->setCallback(CC_CALLBACK_1(MainMenu::menuCloseCallback, this));
	mainMenu->addChild(exitButton);

	return true;
}

void MainMenu::menuCloseCallback(Ref* pSender)
{
	///Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}