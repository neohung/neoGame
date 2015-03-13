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
	//HeroSprite(std::string frameName,std::string pngName,std::string plistName);
	~HeroSprite();
	void doMove(float dt,Vec2 velocity);
	void addAnimFrames(std::string frameName);
	Animate* createAnimate(float time);
	void addMoveLimits(Rect limitRect);
	void clearMoveLimits();
	void cleanAnimFrames();
	float speed;
	ActorStates state;
	SpriteBatchNode* spritebatch;
	Vector<SpriteFrame*>* animFrames;
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