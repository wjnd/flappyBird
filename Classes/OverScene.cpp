#include "OverScene.h"
#include "MenuScene.h"
#include "PlayScene.h"

USING_NS_CC;

Scene* OverLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = OverLayer::create();

	scene->addChild(layer);
	return scene;
}
bool OverLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//init and set pos for score label
	scoreLabel = LabelTTF::create("0", "fonts/Minecrafter.ttf", 30);
	scoreLabel->setPosition(120, 300);
	this->addChild(scoreLabel);

	//for Play button and menu button
	auto menuBtn = MenuItemImage::create("menubutton.png", "menubutton.png", CC_CALLBACK_0(OverLayer::gotoMenuScene, this));
	auto rePlayBtn = MenuItemImage::create("replaybutton.png", "replaybutton.png", CC_CALLBACK_0(OverLayer::gotoPlayScene, this));
	//create menu for 2 buttons
	auto menu = Menu::create(menuBtn, rePlayBtn, nullptr);
	menu->alignItemsHorizontallyWithPadding(50);
	menu->setPosition(120, 120);
	this->addChild(menu);

	return true;
}

void OverLayer::setScore(int _score)
{
	score = _score;
	scoreLabel->setString(String::createWithFormat("%d", score)->getCString());
}
void OverLayer::gotoMenuScene()
{
	auto menuScene = MenuScene::createScene();
	Director::getInstance()->replaceScene(menuScene);
}
void OverLayer::gotoPlayScene()
{
	auto playScene = PlayScene::createScene();
	Director::getInstance()->replaceScene(playScene);
}