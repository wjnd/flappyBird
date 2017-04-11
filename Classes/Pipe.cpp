#include "Pipe.h"

bool Pipe::init()
{
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//velocity X of Pipe
	_velocity = 120;

	//Bottom Pipe
	bottomTexture = Sprite::create("bottomPipe.png");
	//random heigh for bottom Pipe from 1/4 to 1/3 height
	int minY = -(int)(bottomTexture->getContentSize().height / 4);
	int maxY = (int)(bottomTexture->getContentSize().height / 3);
	float randomY = RandomHelper::random_int(minY, maxY);
	bottomTexture->setPosition(0.0f, randomY);
	//create physic body for bottom Pipe
	auto bottomBody = PhysicsBody::createBox(bottomTexture->getContentSize(), PhysicsMaterial(0, 0, 0));
	bottomBody->setDynamic(false);
	//set category bitmask for bottom Pipe
	bottomBody->setCategoryBitmask(eObjectBitmask::PIPE);
	bottomBody->setCollisionBitmask(0);
	bottomBody->setContactTestBitmask(eObjectBitmask::BIRD);
	//assign bottom body to sprite
	bottomTexture->setPhysicsBody(bottomBody);
	//Add to this layer
	this->addChild(bottomTexture);

	//Top Pipe - same as Bottom Pipe
	topTexture = Sprite::create("topPipe.png");
	//220 is space between Top and Bottom Pipe
	topTexture->setPosition(bottomTexture->getPositionX(), bottomTexture->getPositionY() + topTexture->getContentSize().height + 220);
	auto topBody = PhysicsBody::createBox(topTexture->getContentSize(), PhysicsMaterial(0, 0, 0));
	topBody->setDynamic(false);
	topBody->setCategoryBitmask(eObjectBitmask::PIPE);
	topBody->setCollisionBitmask(0);
	topBody->setContactTestBitmask(eObjectBitmask::BIRD);
	topTexture->setPhysicsBody(topBody);
	this->addChild(topTexture);

	//Score line, to increase our score when the bird pass it
	auto scoreLine = Node::create();
	scoreLine->setPosition(Point(bottomTexture->getContentSize().width, bottomTexture->getContentSize().height + 110));
	auto lineBody = PhysicsBody::createBox(Size(1, 300), PhysicsMaterial(0, 0, 0));
	lineBody->setDynamic(false);
	lineBody->setCategoryBitmask(eObjectBitmask::LINE);
	lineBody->setCollisionBitmask(0);
	lineBody->setContactTestBitmask(eObjectBitmask::BIRD);
	scoreLine->setPhysicsBody(lineBody);
	//add it to bottom Pipe
	bottomTexture->addChild(scoreLine);

	//set position
	this->setPosition(origin.x + visibleSize.width + bottomTexture->getContentSize().width / 2, origin.y);

	//move to end point
	_endPositionX = -bottomTexture->getContentSize().width / 2;

	float time = visibleSize.width / _velocity;
	auto endPosition = Vec2(_endPositionX, this->getPositionY());
	//moving
	this->runAction(Sequence::createWithTwoActions(MoveTo::create(time, endPosition), CallFunc::create(CC_CALLBACK_0(Pipe::moveFinished, this))));

	return true;
}

void Pipe::moveFinished()
{
	//remove when move finish
	this->removeFromParent();
}

void Pipe::pause()
{
	Node::pause();

	// pause children
	auto children = this->getChildren();
	for (auto child : children)
	{
		child->pause();
	}
}