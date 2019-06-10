#include "MapScene.h"
#include "tinyxml2/tinyxml2.h"
#include "ui/CocosGUI.h"
#include "MainMenu.h"
#include "GameScene.h"

USING_NS_CC;

Scene* MapScene::createScene() {
	return MapScene::create();
}

bool MapScene::init() {

	if (!Scene::init()) {
		return false;
	}

	//TODO
	///parsing
	std::string mapFileName = "mapConfig/globalMap/globalMap.tmx";
	std::string routesFileName = "config/documents/locationDesctiption/globalMap/globalMapRoutes.xml";

	auto visibleSize = Director::getInstance()->getVisibleSize();

	TMXTiledMap* map = TMXTiledMap::create(mapFileName);
	map->setAnchorPoint(Vec2(0.5, 0.5));
	map->setPosition(visibleSize / 2.f);
	this->addChild(map);

	TMXObjectGroup* mapObjectLoc = map->getObjectGroup("locations");
	ValueVector vectorObjectLocation = mapObjectLoc->getObjects();
	std::vector<Vec2> positionLocation;

	for (auto object : vectorObjectLocation) {
		float x = object.asValueMap().at("x").asFloat();
		float y = object.asValueMap().at("y").asFloat();
		auto type = object.asValueMap().at("type").asString();
		auto name = object.asValueMap().at("name").asString();
		auto nameTextOrigin = object.asValueMap().at("nameTextureOrigin").asString();
		auto nameTextureLight = object.asValueMap().at("nameTextureLight").asString();
		auto fileNameInfo = object.asValueMap().at("fileNameInfo").asString();

		Location* loc = Location::createLocationWithSpriteFrameName(type + ".png");
		loc->setName(name);
		loc->setPosition(x, y);
		loc->setNameTexture(nameTextOrigin, nameTextureLight);
		loc->setFileNameInfo(fileNameInfo);
		_locations.pushBack(loc);
		this->addChild(loc);

		positionLocation.push_back(Vec2(x, y));
	}

	TMXObjectGroup* heroObject = map->getObjectGroup("player");
	ValueMap player = heroObject->getObject("Hero");

	//auto button = Button

	//TODO
	///Сделать нормальную фишку
	_player = GlobalPlayer::createPlayer("texturesConfig/textures/globalMap/horse.png");
	_player->setPosition(player.at("x").asFloat(), player.at("y").asFloat());
	_player->initPositionLocation(positionLocation);
	this->addChild(_player);

	auto button = ui::Button::create("texturesConfig/interface/mainMenu/back.png", "texturesConfig/interface/mainMenu/back1.png");
	button->setPosition(Vec2(50, 710));

	button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN: {
			int debug1 = 0;
			break;
		}
		case ui::Widget::TouchEventType::ENDED: {
			auto director = Director::getInstance();
			//director->getRunningScene()->removeAllChildren();
			director->replaceScene(MainMenu::create());
			break;
		}
		}
	});

	this->addChild(button);

	//TODO
	///задать стартовую позицию из tmx карты
	_player->initStartPostion(0);

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(MapScene::onMouseDown, this);
	mouseListener->onMouseMove = CC_CALLBACK_1(MapScene::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	_parsingRoutes(routesFileName);

	this->scheduleUpdate();

	return true;
}

void MapScene::update(float dt) {
	_player->update(dt);

	auto p1 = _point;
	auto p2 = _player->getCurrentPoint();

	if (_point == _player->getCurrentPoint() && _player->numberOfRunningActions() == 0) {
		auto nameScene = _locations.at(_point)->getFileNameInfo();
		if (nameScene == "nullptr") {
			//TODO
			//вывести окно, которое предупреждает польхователя о недоступности локации
		}
		else {
			auto director = Director::getInstance();
			director->pushScene(GameScene::createScene(nameScene));
			_point = -1;
		}
	}
}

void MapScene::onMouseDown(Event* event) {
	EventMouse* eventMouse = (EventMouse*)event;

	Vec2 posMouse = Vec2(eventMouse->getCursorX(), eventMouse->getCursorY());

	/*for (auto loc : _locations) {
		if (loc->boundingBox().containsPoint(posMouse)) {
			auto llll = loc;
			_character->stopAllActions();
			MoveTo* moveTo = MoveTo::create(3.f, loc->getPosition());
			_character->runAction(moveTo);
		}
	}*/

	for (ssize_t i = 0; i < _locations.size(); ++i) {

		if (_locations.at(i)->getBoundingBox().containsPoint(posMouse)) {
			//TODO
			///smth to do
			///скорость перемещения одинакова
			_point = i;
			_player->moveTo(i);
		}
	}
}

void MapScene::onMouseMove(Event* event) {
	EventMouse* e = (EventMouse*)event;

	Vec2 mousePos = Vec2(e->getCursorX(), e->getCursorY());

	for (auto location : _locations) {
		if (location->boundingBox().containsPoint(mousePos)) {
			location->select();
		}
		else {
			location->dontSelect();
		}
	}
}

//Парсинг xml файла путей глобальной карты
bool MapScene::_parsingRoutes(const std::string& fileName) {
	typedef tinyxml2::XMLDocument XMLDoc;
	typedef tinyxml2::XMLElement XMLElement;
	typedef std::pair<std::string, std::string> STRPair;

	std::vector<STRPair> namePaths;

	XMLDoc doc;
	doc.LoadFile(fileName.c_str());
	if (doc.Error()) {
		return false;
	}

	XMLElement* root = doc.FirstChildElement();
	if (root) {
		XMLElement* eLoc = root->FirstChildElement();
		while (eLoc) {
			//first - откуда
			//second - куда
			STRPair nameLoc;
			nameLoc.first = eLoc->Attribute("name");

			XMLElement* ePos = eLoc->FirstChildElement();
			while (ePos) {
				nameLoc.second = ePos->GetText();
				namePaths.push_back(nameLoc);
				ePos = ePos->NextSiblingElement();
			}
			eLoc = eLoc->NextSiblingElement();
		}
	}
	_initGraph(namePaths);

	return true;
}

void MapScene::_initGraph(const std::vector< std::pair<std::string, std::string> >& vectRoutes) {

	std::vector< std::vector<std::pair<int, int>> > graph(_locations.size());

	for (auto route : vectRoutes) {

		for (int i = 0; i < _locations.size(); ++i) {

			if (route.first == _locations.at(i)->getName()) {
				for (int j = 0; j < _locations.size(); ++j) {
					if (route.second == _locations.at(j)->getName()) {

						auto firstPoint = _locations.at(j)->getPosition();
						auto secondPoint = _locations.at(i)->getPosition();
						int distance = firstPoint.distance(secondPoint);
						
						graph[i].push_back(std::pair<int, int>(j, distance));
						break;
					}
				}
				break;
			}
		}
	}
	_player->initGraphWay(graph);
}

void MapScene::menuCloseCallback(Ref* pSender) {
	Director::getInstance()->end();
}