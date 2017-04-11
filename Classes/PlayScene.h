#pragma once
#include "cocos2d.h"
#include "Bird.h"
#include "Pipe.h"

USING_NS_CC;

class PlayScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	virtual void update(float dt) override;
	CREATE_FUNC(PlayScene);

	void onMouseDown(Event* _event);
	//void onExit();
	bool onContactBegin(PhysicsContact &contact);
private:
	Size visibleSize;
	Vec2 origin;

	//Bird, to control of course
	Bird* bird;
	void birdFall(float dt);

	//create Pipe and store in a list
	void createPipe(float dt);
	//void pipeMoveFinished();
	//std::list<Pipe*> listPipes;

	bool isDead;
	
	//a label to display score
	LabelTTF* scoreLabel;
	int score;
};