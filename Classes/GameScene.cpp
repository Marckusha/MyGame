#include "GameScene.h"
#include "GameInfo.h"
#include "AnimationSet.h"
#include "HorizontalDynamicObject.h"
#include "PeaceBehavior.h"
#include "DamageBehavior.h"
#include "ActorFactory.h"

USING_NS_CC;

Scene* GameScene::createScene(const std::string& str) {

	GameScene *ret = new (std::nothrow) GameScene(str);
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool GameScene::init() {
	if (!Scene::init()) {
		return false;
	}

	auto gameInfo = GameInfo::getInstance();
	_world = gameInfo.getWorld();
	_worldForNPC = GameInfo::getInstance().getWorldForNPC();

	TMXTiledMap* map = TMXTiledMap::create(_fileName);
	map->setName("map");
	this->addChild(map);

	//init animation
	AnimationSet* animSet = AnimationSet::create("texturesConfig/config/animation.xml");
	BaseActor::AnimationMap animMap;
	animMap.insert(BaseActor::AnimationPair("idle", "idle"));
	animMap.insert(BaseActor::AnimationPair("run", "run"));

	auto layer = map->getLayer("staticPlatforms");
	this->createFixtures(layer);
	this->createActors(map->getObjectGroup("peaceActor"));
	this->createKinematicObject(map->getObjectGroup("kinematicObject"));

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

	_healthPoint = std::shared_ptr<HealthPoint>(new HealthPoint(this));
	
	/*DEBUG*/

	//_contList = ContactListener(_player, this);
	//_world->SetContactListener(&_contList);

	

	return true;
}

/*void GameScene::_initObjects() {

	auto world = GameInfo::getInstance().getWorldForNPC();

	std::shared_ptr<ObjectGame> obj(new ObjectGame("apple.jpg", Vec2(1000, 300), world));
	this->addChild(obj->getSprite());
	_objects.push_back(obj);
}*/

void GameScene::update(float dt) {

	float timeStep = 1.f / 60.f;
	_world->Step(dt, 6, 2);
	_worldForNPC->Step(dt, 6, 2);

	_player->update(dt);
	_gameCamera.update(dt);
	_healthPoint->setPosition(_gameCamera.getPosition());

	for (auto actor : _actors) {
		actor->update(dt);
	}

	for (auto object : _dynamicObjects) {
		object->update(dt);
	}

	//object
	/*for (auto object : _objects) {
		object->update(dt);
	}*/

	//logic game

	for (auto actor : _actors) {
		auto boxActor = actor->getSprite()->getBoundingBox();
		auto boxPlayer = _player->getSprite()->getBoundingBox();
		auto leftPos = _player->getSprite()->getPosition();
		auto rightPos = _player->getSprite()->getPosition();

		if (boxActor.containsPoint(leftPos) || boxActor.containsPoint(rightPos)) {
			auto behavior = dynamic_pointer_cast<DamageBehavior>(actor->getBehavior());
			if (behavior && behavior->getActiveDamage()) {
				_healthPoint->update(HealthPoint::State::damage);
			}
			actor->apply(_player);			
		}
	}	
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	if (_isPause) {
		return;
	}

	_player->onKeyPressed(keyCode, event);
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {

	if (keyCode == EventKeyboard::KeyCode::KEY_P) {
		if (!_isPause) {
			this->unscheduleUpdate();
			_isPause = true;
		}
		else {
			this->scheduleUpdate();
			_isPause = false;
		}
	}

	if (_isPause) {
		return;
	}

	_player->onKeyReleased(keyCode, event);
	_gameCamera.onKeyReleased(keyCode, event);

	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		this->unscheduleUpdate();

		Director::getInstance()->popScene();
		auto debug2 = 0;
	}
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

void GameScene::createActors(cocos2d::TMXObjectGroup* objectGroup) {
	for (auto object : objectGroup->getObjects()) {

		NPCInfo info;

		float x = object.asValueMap().at("x").asFloat();
		float y = object.asValueMap().at("y").asFloat();

		info.startPosition = Vec2(x, y);
		info.speed = Vec2(15.f, 0.f);
		
		BaseActor::AnimationMap animMap;
		animMap.insert(BaseActor::AnimationPair("idle", "damageIdle"));
		animMap.insert(BaseActor::AnimationPair("run", "damageRun"));

		info.animationMap = animMap;
		//путь к файлу, который описывает персонажа
		std::string aboutFile = object.asValueMap().at("AboutFile").asString();
		std::string nameAnimation = object.asValueMap().at("NameAnimation").asString();
		float leftPos = object.asValueMap().at("LeftPos").asFloat();
		float rightPos = object.asValueMap().at("RightPos").asFloat();

		std::list<PeaceBehavior::Way> ways;
		ways.push_back(PeaceBehavior::Way(3, Vec2(leftPos, 0)));
		ways.push_back(PeaceBehavior::Way(3, Vec2(rightPos, 0)));

		info.ways = ways;

		if (aboutFile == "damage") {
			std::shared_ptr<ActorFactory> factory(new DamageFactory());
			auto actor = factory->createActor(info);
			this->addChild(actor->getSprite());
			_actors.push_back(actor);
		}
	}
}

/*void GameScene::createRectangularFixture(TMXLayer* layer, int x, int y, float width, float height) {

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
}*/

void GameScene::createKinematicObject(cocos2d::TMXObjectGroup* objectGroup) {
	for (auto object : objectGroup->getObjects()) {

		float x = object.asValueMap().at("x").asFloat();
		float y = object.asValueMap().at("y").asFloat();

		float SizeX = object.asValueMap().at("SizeX").asFloat();
		float SizeY = object.asValueMap().at("SizeY").asFloat();
		float leftPos = object.asValueMap().at("Left").asFloat();
		float rightPos = object.asValueMap().at("Right").asFloat();
		float speed = object.asValueMap().at("Speed").asFloat();

		auto dyn = DynamicObject::createObject("res/block.jpg");
		dyn->init(Vec2(x, y), Vec2(SizeX, SizeY));
		this->addChild(dyn);

		std::shared_ptr<MoveDynamicObject> behavior(new MoveDynamicObject());
		behavior->setSpeed(speed);
		behavior->setBorders(Vec2(leftPos, y), Vec2(rightPos, y));
		dyn->initBehavior(behavior);

		_dynamicObjects.push_back(dyn);
	}
	
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