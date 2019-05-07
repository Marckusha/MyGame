/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "tinyxml2/tinyxml2.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	TMXTiledMap* map = TMXTiledMap::create("mapConfig/globalMap/globalMap.tmx"); 
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
		auto debug2 = 0;

		Location* loc = Location::createBoxWithSpriteFrameName(type + ".png");
		loc->setName(name);
		loc->setPosition(x, y);
		locations.pushBack(loc);
		this->addChild(loc);		
	}

	TMXObjectGroup* heroObject = map->getObjectGroup("player");
	ValueMap player = heroObject->getObject("Hero");

	Sprite* horse = Sprite::create("texturesConfig/textures/globalMap/horse.png");
	horse->setPosition(player.at("x").asFloat(), player.at("y").asFloat());
	this->addChild(horse);

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	_parsingRoutes("config/documents/locationDesctiption/globalMap/globalMapRoutes.xml");
	
    return true;
}

void HelloWorld::onMouseDown(Event* event) {
	EventMouse* eventMouse = (EventMouse*)event;

	/*Test algorithm*/



	Vec2 posMouse = Vec2(eventMouse->getCursorX(), eventMouse->getCursorY());

	for (auto loc : locations) {
		if (loc->boundingBox().containsPoint(posMouse)) {
			int debug2 = 0;
		}
	}
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//Парсинг xml файла путей глобальной карты
bool HelloWorld::_parsingRoutes(const std::string& fileName) {
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


void HelloWorld::_initGraph(const std::vector< std::pair<std::string, std::string> >& vectRoutes) {

	_graph = std::vector < std::vector<std::pair<int, int>> >(locations.size());
	int weight = 1;
		
	for (auto route : vectRoutes) {

		for (int i = 0; i < locations.size(); ++i) {
			if (route.first == locations.at(i)->getName()) {
				for (int j = 0; j < locations.size(); ++j) {
					if (route.second == locations.at(j)->getName()) {
						_graph[i].push_back(std::pair<int, int>(j, weight));
						break;
					}
				}
				break;
			}
		}
	}
}
