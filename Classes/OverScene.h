#pragma once
#include "cocos2d.h"

class OverLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(OverLayer);
	void setScore(int _score);
private:
	void gotoMenuScene();
	void gotoPlayScene();
	int score;
	cocos2d::LabelTTF* scoreLabel;
};