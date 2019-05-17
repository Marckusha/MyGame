#include "MainScene.h"
#include "GameInfo.h"
//#include "Player.h"
#include "AnimationSet.h"

USING_NS_CC;

Scene* MainScene::createScene() {
	return MainScene::create();
}

//TODO
///Переписать всю инициализацию

bool MainScene::init() {
	if (!Scene::init()) {
		return false;
	}
	auto gameInfo = GameInfo::getInstance();
	_world = gameInfo.getWorld();

	TMXTiledMap* map = TMXTiledMap::create("mapConfig/Village1/locationMap.tmx");
	map->setName("map");
	this->addChild(map);

	auto layer = map->getLayer("staticPlatforms");
	this->createFixtures(layer);

//	_actor = std::shared_ptr<Actor>(new Actor());
//	this->addChild(_actor->getSprite());

	this->scheduleUpdate();

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(MainScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto camera = this->getDefaultCamera();
	camera->setPosition(Vec2(visibleSize.width / 2.f, visibleSize.height / 2.f));

	//_contList = ContactListener(_actor, this);
	_world->SetContactListener(&_contList);
	return true;
}

void MainScene::update(float dt) {


}

void MainScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	//_actor->onKeyPressed(keyCode, event);
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	//_actor->onKeyReleased(keyCode, event);

	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || 
		keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW && _isStart) 
	{
		_isStart = false;
		_timer = 0.5f;
		speed /= 2.f;
	}
}

void MainScene::createFixtures(TMXLayer* layer) {
	Size layerSize = layer->getLayerSize();
	auto map = dynamic_cast<TMXTiledMap*>(this->getChildByName("map"));
	auto mapSize = map->getMapSize();
	auto tileSize = map->getTileSize();

	for (int y = 0; y < layerSize.height; ++y) {
		int countTile = 0;
		for (int x = 0; x < layerSize.width; ++x) {
			auto tileSprite = layer->getTileAt(Vec2(x, y));
			if (tileSprite) {
				countTile++;
			}
			else if (countTile > 0) {
				int _y = mapSize.height - y;
				float _x = x;// + countTile / 2.f;
				float posX = (x + 1) * tileSize.width - (tileSize.width) / 2.f;
				Vec2 objectPos = Vec2(posX - (countTile + 1) * tileSize.width / 2.f, (_y)* tileSize.height - tileSize.height / 2.f);
				Vec2 objSize(tileSize.width * countTile, tileSize.height);
				//StaticObject obj(objectPos, objSize);
				//StaticObject obj(Vec2((x * map->getTileSize().width),100), Vec2(16, 16));
				//this->addChild(obj.getSprite());
				countTile = 0;
			}
		}
		if (countTile > 0) {
			int _y = mapSize.height - y;
			float _x = layerSize.width;// + countTile / 2.f;
			float posX = (_x + 1) * tileSize.width - (tileSize.width) / 2.f;
			Vec2 objectPos = Vec2(posX - (countTile + 1) * tileSize.width / 2.f, (_y)* tileSize.height - tileSize.height / 2.f);
			Vec2 objSize(tileSize.width * countTile, tileSize.height);
			//StaticObject obj(objectPos, objSize);
			//StaticObject obj(Vec2((x * map->getTileSize().width),100), Vec2(16, 16));
			//this->addChild(obj.getSprite());
			countTile = 0;
		}
	}
}

void MainScene::createRectangularFixture(TMXLayer* layer, int x, int y, float width, float height) {

	GameInfo& info = GameInfo::getInstance();
	auto world = info.getWorld();
	auto map = dynamic_cast<TMXTiledMap*>(this->getChildByName("map"));
	int debug2 = 0;

	// get position & size
	auto p = layer->getPositionAt(Point(x, y));
	auto tileSize = map->getTileSize();
	const float pixelsPerMeter = 32.0f;

	// note: creating the 'world' member variable
	// is discussed in the next chapter

	// create the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(
		(p.x + (tileSize.width / 2.0f)) / pixelsPerMeter,
		(p.y + (tileSize.height / 2.0f)) / pixelsPerMeter
	);
	b2Body* body = world->CreateBody(&bodyDef);

	// define the shape
	b2PolygonShape shape;
	shape.SetAsBox(
		(tileSize.width / pixelsPerMeter) * 0.5f * width,
		(tileSize.width / pixelsPerMeter) * 0.5f * height
	);

	// create the fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;
	//fixtureDef.filter.categoryBits = kFilterCategoryLevel;
	fixtureDef.filter.maskBits = 0xffff;
	body->CreateFixture(&fixtureDef);
}

/*Unit* MainScene::addObject(std::string className, Vec2 pos)
{
	auto world = GameInfo::getInstance().getWorld();
	// create the object
	Unit* o = nullptr;
	if (className == "Player")
		o = new Player();

	// process the new object
	if (o != nullptr)
	{
		o->setProperties(pos.x, pos.y);
		o->initWithFile("res/horse.png");
		//o->addSprite();
		o->addBodyToWorld(world);
		//o->addSprite("res/horse.png");
		//o->addFixturesToBody();
		this->addChild(o);
	}
	return o;
}*/