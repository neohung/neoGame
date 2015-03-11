#ifndef __HOMELAYER_H__
#define __HOMELAYER_H__

#include "cocos2d.h"
#include "GameLayer.h"

using namespace cocos2d;

class HomeLayer : public Layer{
public:
	HomeLayer(GameLayer* gameLayer);
	~HomeLayer();
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
private:
	void _init_touch();
	bool _isInTouchArea(Touch* touch);
private:
	Rect _touchArea;
	GameLayer* _gameLayer;
};

#endif