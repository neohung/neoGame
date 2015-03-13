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

void HeroSprite::addAnimFrames(std::string frameName)
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	SpriteFrame* frame = cache->getSpriteFrameByName(frameName);
	animFrames->pushBack(frame);
}
Animate* HeroSprite::createAnimate(float playTime)
{
	return Animate::create(Animation::createWithSpriteFrames(*animFrames, playTime));
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
	//log("DoMove(%lf,%lf)",velocity.x,velocity.y);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Rect boundingBox = getBoundingBox();
	//log("%lf,%lf",velocity.x*speed,velocity.y*speed);
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
		//log("size:%d,Limit(%lf,%lf,%lf,%lf) ",_moveLimit->size(),limitRect.getMinX(),limitRect.getMinY(),limitRect.getMaxX(),limitRect.getMaxY());
	}
	//log("-------->%lf,%lf",velocity.x*speed,velocity.y*speed);
	this->runAction(MoveBy::create(dt,velocity*speed));
	//log("SP(%lf,%lf,%lf,%lf) ",getBoundingBox().getMinX(),getBoundingBox().getMinY(), getBoundingBox().getMaxX(),getBoundingBox().getMaxY());
}