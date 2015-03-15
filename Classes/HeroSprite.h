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
	HeroSprite(std::string frameName, std::string pngFileName, std::string plistName, int zorder);
	~HeroSprite();
	void doMove(float dt,Vec2 velocity);
	void addMoveLimits(Rect limitRect);
	void clearMoveLimits();
	void initAnimation(std::string heroName);
	float speed;
	ActorStates state;
	SpriteBatchNode* spritebatch;
	Vector<SpriteFrame*>* animFrames;
	std::string animationPrefixName;
	/*
	static void* operator new (std::size_t size) {
        void *pHeroSprite = malloc( size );
        if (pHeroSprite){
        	return pHeroSprite;
        }
        return NULL;
	}
	*/
 
private:
	
private:
	 std::vector<cocos2d::Rect>* _moveLimit;
};

#endif