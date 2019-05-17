#include "GameScene.h"
#include "GameInfo.h"
#include "AnimationSet.h"
#include "HorizontalDynamicObject.h"
#include "PeaceBehavior.h"

USING_NS_CC;

Scene* GameScene::createScene() {
	return GameScene::create();
}

bool GameScene::init() {
	if (!Scene::init()) {
		return false;
	}
	auto gameInfo = GameInfo::getInstance();
	_world = gameInfo.getWorld();
	_worldForNPC = GameInfo::getInstance().getWorldForNPC();
	

	TMXTiledMap* map = TMXTiledMap::create("mapConfig/Village1/locationMap.tmx");
	map->setName("map");
	this->addChild(map);

	auto layer = map->getLayer("staticPlatforms");
	this->createFixtures(layer);

	AnimationSet* animSet = AnimationSet::create("texturesConfig/config/animation.xml");
	BaseActor::AnimationMap animMap;
	animMap.insert(BaseActor::AnimationPair("idle", "idle"));
	animMap.insert(BaseActor::AnimationPair("run", "run"));

	//behavior actor
	_baseActor = std::shared_ptr<Actor>(new Actor(animMap, Vec2(100, 300), _worldForNPC));
	this->addChild(_baseActor->getSprite());	
	_baseActor->setSpeed(Vec2(15.f, 0));

	std::list<PeaceBehavior::Way> ways;
	ways.push_back(PeaceBehavior::Way(3, Vec2(600, 0)));
	ways.push_back(PeaceBehavior::Way(3, Vec2(100, 0)));
	ways.push_back(PeaceBehavior::Way(2, Vec2(1000, 0)));
	std::shared_ptr<PeaceBehavior> _peaceBehavior(new PeaceBehavior(_baseActor, ways));
	_baseActor->setBehavior(_peaceBehavior);

	_player = std::shared_ptr<Player>(new Player(animMap, Vec2(500, 300), _world));
	this->addChild(_player->getSprite());

	this->scheduleUpdate();

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//camera
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto camera = this->getDefaultCamera();
	camera->setPosition(Vec2(visibleSize.width / 2.f, visibleSize.height / 2.f));
	_gameCamera = GameCamera(camera, _player);
	
	/*DEBUG*/

	/*_actor = std::shared_ptr<Actor>(new Actor());
	this->addChild(_actor->getSprite());*/
	
	//std::shared_future<BehaviorDynamicObject> behavior(new BehaviorDynamicObject());

	//_contList = ContactListener(_player, this);
	//_world->SetContactListener(&_contList);

	/*_dyn = DynamicObject::createObject("res/red.jpg");
	_dyn->init(Vec2(600, 200), Vec2(100, 50));
	this->addChild(_dyn);

	std::shared_ptr<MoveDynamicObject> behavior(new MoveDynamicObject());
	behavior->setSpeed(5.f);
	behavior->setBorders(Vec2(600, 240), Vec2(1500, 240));
	_dyn->initBehavior(behavior);*/

	return true;
}

void GameScene::update(float dt) {

	float timeStep = 1.f / 60.f;
	_world->Step(dt, 6, 2);
	_worldForNPC->Step(dt, 6, 2);

	_baseActor->update(dt);
	_player->update(dt);
	//_dyn->update(dt);
	_gameCamera.update(dt);
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	_player->onKeyPressed(keyCode, event);
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	_player->onKeyReleased(keyCode, event);
	_gameCamera.onKeyReleased(keyCode, event);
}

void GameScene::createFixtures(TMXLayer* layer) {
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
				/*PlatformerObject* platformerObject = PlatformerObject::createObject("res/red.jpg");
				platformerObject->init(objectPos, objSize);
				this->addChild(platformerObject);*/
				//StaticObject obj(objectPos, objSize);
				StaticObject* obj = StaticObject::createObject("res/red.jpg");
				obj->init(objectPos, objSize);
				obj->setDebug(false);
				this->addChild(obj);
				countTile = 0;
			}
		}
		if (countTile > 0) {
			int _y = mapSize.height - y;
			float _x = layerSize.width;// + countTile / 2.f;
			float posX = (_x + 1) * tileSize.width - (tileSize.width) / 2.f;
			Vec2 objectPos = Vec2(posX - (countTile + 1) * tileSize.width / 2.f, (_y)* tileSize.height - tileSize.height / 2.f);
			Vec2 objSize(tileSize.width * countTile, tileSize.height);
			StaticObject* obj = StaticObject::createObject("res/red.jpg");
			obj->init(objectPos, objSize);
			obj->setDebug(false);
			this->addChild(obj);
			//StaticObject obj(objectPos, objSize);
			//StaticObject obj(Vec2((x * map->getTileSize().width),100), Vec2(16, 16));
			//this->addChild(obj.getSprite());
			countTile = 0;
		}
	}
}

void GameScene::createRectangularFixture(TMXLayer* layer, int x, int y, float width, float height) {

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