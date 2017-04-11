#pragma once

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;
class Bird : public Sprite
{
public:
	CREATE_FUNC(Bird);

	virtual bool init() override;
	virtual void update(float dt) override;	//update bird

	void flap();	//bird fly
	void fall();	//bird fall
	
	void setDead(bool dead);
	bool isDead();

private:

	Size _visibleSize;

	bool _isFalling;	//check if bird is falling
	bool _isDead;
	Vec2 _velocity;	//velocity of Bird 
	float _rotation;		//rotation of bird
};