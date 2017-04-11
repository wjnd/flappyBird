#include "Bird.h"
#include "Definitions.h"


bool Bird::init()
{
	if (!this->initWithFile("bird.png"))
	{
		return false;
	}
	//get some values of the screen
	auto origin = Director::getInstance()->getVisibleOrigin();
	_visibleSize = Director::getInstance()->getVisibleSize();

	this->setPosition(origin.x + _visibleSize.width / 2, origin.y + _visibleSize.height / 2);

	//create physic body for bird, this use to check collision
	auto birdBody = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0, 0, 0));
	// assign category bitmask for bird to check collision - It means I'm a BIRD
	birdBody->setCategoryBitmask(eObjectBitmask::BIRD);
	//assign collision bitmask for body - It means I can collission with ...
	birdBody->setCollisionBitmask(0);
	birdBody->setContactTestBitmask(eObjectBitmask::PIPE | eObjectBitmask::LINE);
	
	this->setPhysicsBody(birdBody);

	//And init some default value for member class var
	_isFalling = true;
	_isDead = false;
	_velocity = Vec2(0, 0);
	_rotation = 0.0f;

	this->scheduleUpdate();
	return true;
}

void Bird::update(float dt)
{
	//if Bird is falling - it dead when hit ground
	if (_isFalling)
	{
		//If it's still in position higher than ground
		if (this->getPositionY() > this->getContentSize().height / 2)
		{
			//bird is falling, update Its posY and rotation
			_velocity.y += -1;
			_rotation += 3;
		}
		else
		{
			// no fall anymore, no rotation, it's in ground and die
			_velocity.y = 0;
			_rotation = 0;
			_isDead = true;
			this->setPositionY(this->getContentSize().height / 2);
		}
	}
	else //not falling
	{
		//If it's under the ceiling
		if (this->getPositionY() < _visibleSize.height - this->getContentSize().height / 2)
		{
			//Bird is flying, update Its posY and rotation
			_velocity.y = 10;
			_rotation += -10;
		}
		else  //Bird is hit ceiling
		{
			_velocity.y = 0;
			_rotation = 0;
		}
	}

	//finally, set pos and rotation for Bird
	this->setPosition(Vec2(this->getPositionX(), this->getPositionY() + _velocity.y));
	this->setRotation(_rotation);
}

void Bird::flap()
{
	_isFalling = false;
}

void Bird::fall()
{
	_isFalling = true;
}

void Bird::setDead(bool dead)
{
	_isDead = dead;
}

bool Bird::isDead()
{
	return _isDead;
}