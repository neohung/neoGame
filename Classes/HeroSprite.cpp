#include "HeroSprite.h"

using namespace cocos2d;

HeroSprite::HeroSprite(std::string frameName, std::string pngFileName, std::string plistName, int zorder)
{
	spritebatch = SpriteBatchNode::create(pngFileName);
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(plistName);
	//if (!spritebatch) {delete this; return;}
	if(initWithSpriteFrameName(frameName.c_str()))
	{
		state = kStateIdle;
		speed = 2.0f;
		_moveLimit = new std::vector<cocos2d::Rect>();
		_moveLimit->clear();

		animFrames = new Vector<SpriteFrame*>();
		spritebatch->addChild(this,zorder);
	}
}

HeroSprite::~HeroSprite()
{

}

void HeroSprite::addMoveLimits(Rect limitRect)
{
	_moveLimit->push_back(limitRect);
}

void HeroSprite::clearMoveLimits()
{
	_moveLimit->clear();
}

void HeroSprite::doMove(float dt,Vec2 velocity)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Rect boundingBox = getBoundingBox();
	for(int i=0;i<_moveLimit->size();i++)
	{
		Rect* limitRect = &_moveLimit->at(i);
		bool isOutofLeftX = (!limitRect->containsPoint(Vec2(getBoundingBox().getMinX()+velocity.x*speed,getPositionY())));
		bool isOutofRightX = (!limitRect->containsPoint(Vec2(getBoundingBox().getMaxX()+velocity.x*speed,getPositionY())));
		bool isOutofTopY = (!limitRect->containsPoint(Vec2(getPositionX(),getBoundingBox().getMinY()+velocity.y*speed)));
		bool isOutofBottomY = (!limitRect->containsPoint(Vec2(getPositionX(),getBoundingBox().getMaxY()+velocity.y*speed)));
		if (isOutofLeftX || isOutofRightX)
		{
			velocity.x = 0;
		}
		if (isOutofTopY || isOutofBottomY)
		{
			velocity.y = 0;
		}
	}
	this->runAction(MoveBy::create(dt,velocity*speed));
}

void HeroSprite::initAnimation(std::string heroName)
{
	//overload this function if you need
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> animFrames;
	animationPrefixName = heroName;
	//animationPrefixName = heroName.c_str();
	char str[100] = {0};
	float animTime = 0.2;
	for(int i = 0; i < 4; i++) 
	{
		sprintf(str, "%sf_%01d.png", animationPrefixName.c_str(),i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animFrames, animTime);
	sprintf(str, "%s_%s", animationPrefixName.c_str(),"AttackF");
	AnimationCache::getInstance()->addAnimation(animation, str);
	animFrames.clear();
	for(int i = 4; i < 7; i++) 
	{
		sprintf(str, "%sf_%01d.png", animationPrefixName.c_str(),i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	animation = Animation::createWithSpriteFrames(animFrames, animTime);
	sprintf(str, "%s_%s", animationPrefixName.c_str(),"WalkF");
	AnimationCache::getInstance()->addAnimation(animation, str);
	animFrames.clear();
	for(int i = 7; i < 9; i++) 
	{
		sprintf(str, "%sf_%01d.png", animationPrefixName.c_str(),i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	animation = Animation::createWithSpriteFrames(animFrames, animTime);
	sprintf(str, "%s_%s", animationPrefixName.c_str(),"DeadF");
	AnimationCache::getInstance()->addAnimation(animation, str);

	animFrames.clear();
	for(int i = 0; i < 4; i++) 
	{
		sprintf(str, "%s_%01d.png", animationPrefixName.c_str(),i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	animation = Animation::createWithSpriteFrames(animFrames,animTime);
	sprintf(str, "%s_%s", animationPrefixName.c_str(),"AttackB");
	AnimationCache::getInstance()->addAnimation(animation, str);
	animFrames.clear();
	for(int i = 4; i < 7; i++) 
	{
		sprintf(str, "%s_%01d.png", animationPrefixName.c_str(),i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	animation = Animation::createWithSpriteFrames(animFrames, animTime);
	sprintf(str, "%s_%s", animationPrefixName.c_str(),"WalkB");
	AnimationCache::getInstance()->addAnimation(animation, str);
	animFrames.clear();
	for(int i = 7; i < 9; i++) 
	{
		sprintf(str, "%s_%01d.png", animationPrefixName.c_str(),i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	animation = Animation::createWithSpriteFrames(animFrames, animTime);
	sprintf(str, "%s_%s", animationPrefixName.c_str(),"DeadB");
	AnimationCache::getInstance()->addAnimation(animation, str);
}