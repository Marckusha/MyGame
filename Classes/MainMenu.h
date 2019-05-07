#pragma once
#include "cocos2d.h"

class MainMenu : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init() override;

	void menuCloseCallback(cocos2d::Ref* pSender);
	
	CREATE_FUNC(MainMenu);

private:
	bool _isNew = true;

	std::string _playText = "";
	std::string _exitText = "";
	std::string _continueText = "";
	std::string _langText = "";
	std::string _backText = "";
};