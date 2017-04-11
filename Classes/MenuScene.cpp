#include "MenuScene.h"
#include "PlayScene.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MenuScene::create();

	scene->addChild(layer);
	return scene;
}
///////////
bool MenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//Title game on Menu
	auto titleLabel = Label::createWithSystemFont("Flappy Bird", "Arial", 15);
	titleLabel->setPosition(Vec2(200, 50));
	this->addChild(titleLabel);

	//Play Button on Menu
	auto playButton = MenuItemImage::create("playbutton.png", "playbutton.png", CC_CALLBACK_0(MenuScene::gotoPlayScene, this));
	auto menu = Menu::create(playButton, nullptr);
	menu->setPosition(Vec2(300, 50));
	this->addChild(menu);

	return true;
}
//////////////////////
void MenuScene::gotoPlayScene()
{
	auto playscene = PlayScene::createScene();
	Director::getInstance()->replaceScene(playscene);
}