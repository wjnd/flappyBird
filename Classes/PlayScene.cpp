#include "PlayScene.h"
#include "OverScene.h"

Scene* PlayScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	
	auto layer = PlayScene::create();
	scene->addChild(layer);
	
	return scene;
}
bool PlayScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	//set background for Game if have 
	//
	//Player - create Bird
	bird = Bird::create();
	this->addChild(bird);

	//Event listener - here we create for Mouse event listener
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(PlayScene::onMouseDown, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);

	//Contact listener for collision, setContactTestBitMask call it when have collision
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PlayScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	//Update - It call our update function for each frame
	this->scheduleUpdate();

	//Create schedule to create new Pipe each 2 seconds
	this->schedule(schedule_selector(PlayScene::createPipe), 2.0f);

	//Create Pipe
	auto pipe = Pipe::create();
	this->addChild(pipe);

	//For score
	score = 0;
	scoreLabel = LabelTTF::create("0", "Arial", 30);
	scoreLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + (visibleSize.height / 6) * 5);
	this->addChild(scoreLabel, 50);
	
	return true;
}

void PlayScene::update(float dt)
{

	//If die
	if (bird->isDead())
	{
		//remove score Label
		this->removeChild(scoreLabel);
		//Pause game
		this->pause();
		//pause for all children
		auto chils = this->getChildren();
		for (auto child : chils)
		{
			child->pause();
		}

		//Create Over scene 
		auto overLayer = OverLayer::create();
		overLayer->setScore(score);
		overLayer->setPosition(origin.x, origin.y);
		this->addChild(overLayer, 110);
	}
}

void PlayScene::onMouseDown(Event* _event)
{
	EventMouse* mouse = (EventMouse*)_event;
	if (mouse->getMouseButton() == MOUSE_BUTTON_LEFT)
	{
		//If mouse left click, bird fly
		bird->flap();
		//and call fall function each 0.1 sec
		this->scheduleOnce(schedule_selector(PlayScene::birdFall), 0.1f);
	}
}

void PlayScene::birdFall(float dt)
{
	bird->fall();
}

void PlayScene::createPipe(float dt)
{
	auto pipe = Pipe::create();
	this->addChild(pipe);
}

bool PlayScene::onContactBegin(PhysicsContact &contact)
{
	//this function handling when have collision
	// first, we get 2 objects which have collision 
	auto shapeA = contact.getShapeA();
	auto shapeB = contact.getShapeB();

	//If A and B is PIPE and BIRD >>> bird die
	if (shapeA->getCategoryBitmask() == eObjectBitmask::PIPE && shapeB->getCategoryBitmask() == eObjectBitmask::BIRD
		|| shapeB->getCategoryBitmask() == eObjectBitmask::PIPE && shapeA->getCategoryBitmask() == eObjectBitmask::BIRD)
	{
		bird->setDead(true);
	}
	else
	{
		//If A and B is BIRD and LINE, increase score for player
		if (shapeA->getCategoryBitmask() == eObjectBitmask::LINE && shapeB->getCategoryBitmask() == eObjectBitmask::BIRD
			|| shapeB->getCategoryBitmask() == eObjectBitmask::LINE && shapeA->getCategoryBitmask() == eObjectBitmask::BIRD)
		{
			score++;
			scoreLabel->setString(String::createWithFormat("%d", score)->getCString());
		}
	}
	return true;
}