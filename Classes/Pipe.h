#pragma once
#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;
class Pipe : public Node
{
public:
	CREATE_FUNC(Pipe);
	virtual bool init() override;
	virtual void pause() override;
	void moveFinished();	
	bool isMoveFinished;
private:
	Sprite* topTexture;
	Sprite* bottomTexture;

	float _velocity;
	float _endPositionX;
};