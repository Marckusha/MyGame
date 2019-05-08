#include "MapScene.h"
#include "tinyxml2/tinyxml2.h"

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

	for (auto object : vectorObjectLocation) {
		float x = object.asValueMap().at("x").asFloat();
		float y = object.asValueMap().at("y").asFloat();
		auto type = object.asValueMap().at("type").asString();
		auto name = object.asValueMap().at("name").asString();
		auto nameTextOrigin = object.asValueMap().at("nameTextureOrigin").asString();
		auto nameTextureLight = object.asValueMap().at("nameTextureLight").asString();

		Location* loc = Location::createBoxWithSpriteFrameName(type + ".png");
		loc->setName(name);
		loc->setPosition(x, y);
		loc->setNameTexture(nameTextOrigin, nameTextureLight);
		_locations.pushBack(loc);
		this->addChild(loc);
	}

	//TODO
	///задать стартовую позицию из tmx карты
	_startPosition = 0;

	TMXObjectGroup* heroObject = map->getObjectGroup("player");
	ValueMap player = heroObject->getObject("Hero");

	//TODO
	///Сделать нормальную фишку
	_character = Sprite::create("texturesConfig/textures/globalMap/horse.png");
	_character->setPosition(player.at("x").asFloat(), player.at("y").asFloat());
	this->addChild(_character);

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(MapScene::onMouseDown, this);
	mouseListener->onMouseMove = CC_CALLBACK_1(MapScene::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	_parsingRoutes(routesFileName);

	return true;
}

void MapScene::onMouseDown(Event* event) {
	EventMouse* eventMouse = (EventMouse*)event;

	/*Test algorithm*/

	Vec2 posMouse = Vec2(eventMouse->getCursorX(), eventMouse->getCursorY());

	/*for (auto loc : _locations) {
		if (loc->boundingBox().containsPoint(posMouse)) {
			auto llll = loc;
			_character->stopAllActions();
			MoveTo* moveTo = MoveTo::create(3.f, loc->getPosition());
			_character->runAction(moveTo);
		}
	}*/

	for (size_t i = 0; i < _locations.size(); ++i) {

		if (_locations.at(i)->getBoundingBox().containsPoint(posMouse)) {
			_initPath(i);
			//TODO
			///smth to do
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

	_graph = std::vector < std::vector<std::pair<int, int>> >(_locations.size());

	for (auto route : vectRoutes) {

		for (int i = 0; i < _locations.size(); ++i) {

			if (route.first == _locations.at(i)->getName()) {
				for (int j = 0; j < _locations.size(); ++j) {
					if (route.second == _locations.at(j)->getName()) {

						auto firstPoint = _locations.at(j)->getPosition();
						auto secondPoint = _locations.at(i)->getPosition();
						int distance = firstPoint.distance(secondPoint);
						
						_graph[i].push_back(std::pair<int, int>(j, distance));
						break;
					}
				}
				break;
			}
		}
	}
}

void MapScene::_initPath(int positionTo) {

	const int INF = 10000000;

	//количество вершин
	int n = _graph.size();

	//граф смежности
	//_graph

	//стартовая позиция
	int s = _startPosition;

	//минимальный вес до каждой вершини;?
	std::vector<int> d(n, INF), p(n);

	//вес стартовой позиции всегда равне нулю
	d[s] = 0;
	//посещенные вершины
	std::vector<bool> u(n);

	for (int i = 0; i < n; ++i) {
		int v = -1;
		for (int j = 0; j < n; ++j) {
			if (!u[j] && (v == -1 || d[j] < d[v])) {
				v = j;
			}
		}
		if (d[v] == INF) {
			break;
		}
		u[v] = true;

		for (int j = 0; j < _graph[v].size(); ++j) {
			int to = _graph[v][j].first;
			int len = _graph[v][j].second;

			if (d[v] + len < d[to]) {
				d[to] = d[v] + len;
				p[to] = v;
			}
		}
	}

	_path.clear();
	for (int v = positionTo; v != s; v = p[v])
		_path.push_back(v);
	_path.push_back(s);
	reverse(_path.begin(), _path.end());
}

void MapScene::menuCloseCallback(Ref* pSender) {
	Director::getInstance()->end();
}