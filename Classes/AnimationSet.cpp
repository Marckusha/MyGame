#include "AnimationSet.h"
#include "tinyxml2/tinyxml2.h"
#include <iomanip>

USING_NS_CC;

AnimationSet* AnimationSet::create(const std::string& fileName) {
	auto ret = AnimationSet::create();
	ret->initWithFile(fileName);
	ret->autorelease();
	return ret;
}

bool AnimationSet::init() {
	return true;
}

bool AnimationSet::initWithFile(const std::string& fileName) {

	//to do cod

	typedef tinyxml2::XMLDocument XMLDoc;
	typedef tinyxml2::XMLElement XMLNode;

	XMLDoc doc;
	doc.LoadFile(fileName.c_str());
	if (doc.Error()) {
		return true;
	}

	XMLNode* eAnims = doc.FirstChildElement("Animations");

	if (eAnims) {
		XMLNode* eAnim = eAnims->FirstChildElement("animation");

		while (eAnim) {
			std::string key = eAnim->Attribute("key");
			std::string source = eAnim->Attribute("source");
			int countFrame = eAnim->IntAttribute("countFrame");
			float duration = 0.1f;//eAnim->FloatAttribute("duration");

			auto cacher = SpriteFrameCache::getInstance();
			cacher->addSpriteFramesWithFile(source);
			
			auto animCacher = AnimationCache::getInstance();

			Vector<SpriteFrame*> animFrames;
			//Vector<SpriteFrame*> animFramesReverse;

			for (int i = 1; i <= countFrame; ++i) {
				std::stringstream ss;
				ss << key << i << ".png";
				animFrames.pushBack(cacher->getSpriteFrameByName(ss.str()));
				//animFramesReverse.pushBack(cacher->getSpriteFrameByName(ss.str())->setro);
			}

			Animation* anim = Animation::createWithSpriteFrames(animFrames, duration);
			animCacher->addAnimation(anim, key);
			_animations.insert(key, anim);

			eAnim = eAnim->NextSiblingElement();
		}
	}

	return true;
}