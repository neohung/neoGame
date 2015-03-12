#ifndef __HOMELAYER_H__
#define __HOMELAYER_H__

#include "cocos2d.h"
#include "GameLayer.h"

using namespace cocos2d;

enum HomeButtons
{
	kTagStartBtn = 0
};

class HomeLayer : public Layer{
public:
	HomeLayer(GameLayer* gameLayer);
	~HomeLayer();
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	void showMenu(float dt);
	void startGame();
	void onButtonPress(Ref* pSender);
	//EventListenerTouchOneByOne* touchlistener;
private:
	void _init_touch();
	bool _isInTouchArea(Touch* touch);
	void _preLoadData();
private:
	DrawNode* _drawNode;
	Sprite* _sp;
	Animate* _spAnimate;
	Rect _touchArea;
	GameLayer* _gameLayer;
};

#endif