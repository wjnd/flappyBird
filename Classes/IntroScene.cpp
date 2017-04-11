#include "IntroScene.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"
USING_NS_CC;

Scene* IntroScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = IntroScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool IntroScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    //Our code here - go go go 
	auto introBackground = Sprite::create("Pug_12.jpg");
	introBackground->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(introBackground);
	this->scheduleOnce(schedule_selector(IntroScene::gotoMenuScene), 2.0f);
    return true;
}

void IntroScene::gotoMenuScene(float dt)
{
	auto menuScene = MenuScene::createScene();
	Director::getInstance()->replaceScene(menuScene);
}

void IntroScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
