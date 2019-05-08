#pragma once
#include "cocos2d.h"

/** @class StartScene
* @brief —цена отображаетс€ в самом начале запуска игры
*/

class StartScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void update(float dt);

	CREATE_FUNC(StartScene);

private:
	float _timer = 0.f;
};
