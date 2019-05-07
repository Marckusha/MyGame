#pragma once
#include "cocos2d.h"

class AnimationSet : public cocos2d::Ref {
public:
	static AnimationSet* create(const std::string& fileName);

	bool init();

	bool initWithFile(const std::string& fileName);

	cocos2d::Animation* getAnimation(const std::string& key) {
		return _animations.at(key);
	}

	CREATE_FUNC(AnimationSet);
private:
	cocos2d::Map<std::string, cocos2d::Animation*> _animations;
};