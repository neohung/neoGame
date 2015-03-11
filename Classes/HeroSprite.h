#ifndef __HEROSPRITE_H__
#define __HEROSPRITE_H__

#include "cocos2d.h"


using namespace cocos2d;

enum
{
    kActionIdleAnimationTag = 1000,
    kActionAttackAnimationTag = 1001
};

enum ActorStates
{
    kStateNothing = 0,
 	kStateIdle   
};


class HeroSprite : public Sprite{
public:
	HeroSprite(std::string filename);
	~HeroSprite();
	void doMove(Vec2 velocity);
	float speed;
	ActorStates state;
private:
private:
};

#endif