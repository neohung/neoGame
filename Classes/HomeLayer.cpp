#include "HomeLayer.h"

HomeLayer::HomeLayer(GameLayer* gameLayer)
{
	_gameLayer = gameLayer;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto sp = Sprite::create("neko.png");
	sp->setPosition(visibleSize.width/2,visibleSize.height/2);
	addChild(sp);
	_touchArea = Rect(sp->getPosition().x - sp->getContentSize().width/2,sp->getPosition().y - sp->getContentSize().height/2,sp->getContentSize().width,sp->getContentSize().height);
	_init_touch();
}

HomeLayer::~HomeLayer()
{
	
}

void HomeLayer::_init_touch()
{
	auto touchlistener = EventListenerTouchOneByOne::create();  
	touchlistener->onTouchBegan = CC_CALLBACK_2(HomeLayer::onTouchBegan, this);  
	touchlistener->onTouchMoved = CC_CALLBACK_2(HomeLayer::onTouchMoved, this);  
	touchlistener->onTouchEnded = CC_CALLBACK_2(HomeLayer::onTouchEnded, this);  
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchlistener, this);  
}

bool HomeLayer::_isInTouchArea(Touch* touch)
{
	Point pt = this->convertToNodeSpace(touch->getLocation());
	return _touchArea.containsPoint(pt);
}

bool HomeLayer::onTouchBegan(Touch* touch, Event* event){ 
Point pt = this->convertToNodeSpace(touch->getLocation()); 
	//log("HomeLayer::onTouchBegan(%lf,%lf)",pt.x,pt.y);
	return _isInTouchArea(touch);
}

void HomeLayer::onTouchEnded(Touch* touch, Event* event){  
	Point pt = this->convertToNodeSpace(touch->getLocation());
	// set inVisible
	this->setVisible(false);
	//_showMenu;	
}

void HomeLayer::onTouchMoved(Touch* touch, Event* event){ 
	auto xDelta = touch->getDelta().x;
	auto yDelta = touch->getDelta().y;
}
