#include "HomeLayer.h"
#include "SimpleAudioEngine.h"

HomeLayer::HomeLayer(GameLayer* gameLayer)
{
	_gameLayer = gameLayer;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	_drawNode = DrawNode::create();  
	Vec2 shape[] = { Vec2(0,visibleSize.height), Vec2(visibleSize.width,visibleSize.height), Vec2(visibleSize.width,0), Vec2(0,0) };
	_drawNode->drawPolygon(shape, sizeof(shape)/sizeof(shape[0]), Color4F(0.8,0.8,0.8,0.9), 2, Color4F(0,0,1,1));  
	this->addChild(_drawNode);
	_sp = Sprite::create("neko.png");
	_sp->setPosition(visibleSize.width/2,visibleSize.height/2);
	addChild(_sp,0);
	auto spRepeatForever = RepeatForever::create(Sequence::create(DelayTime::create(2),ScaleTo::create(0.5,1.08),ScaleTo::create(0.5,1),DelayTime::create(0),NULL));
	_sp->runAction(spRepeatForever);
	spRepeatForever:setTag(1);
	spRepeatForever->retain(); 
	auto label = Label::createWithBMFont("futura-48.fnt", "Neo Present",TextHAlignment::CENTER);
	label->setPosition(_sp->getPosition().x,_sp->getPosition().y+label->getContentSize().height*2);
	addChild(label,10);
	_preLoadData();
	_touchArea = Rect(_sp->getPosition().x - _sp->getContentSize().width/2,_sp->getPosition().y - _sp->getContentSize().height/2,_sp->getContentSize().width,_sp->getContentSize().height);
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
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point pt = this->convertToNodeSpace(touch->getLocation());
	// set inVisible
	auto move = MoveBy::create(3, Vec2(visibleSize.width*0.25,0));
	auto move_ease_out = EaseOut::create(move, 2.5f);
	_sp->runAction(move_ease_out);
	_sp->stopActionByTag(1);
	scheduleOnce(schedule_selector(HomeLayer::showMenu), 2.5);
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);	
}

void HomeLayer::onTouchMoved(Touch* touch, Event* event){ 
	auto xDelta = touch->getDelta().x;
	auto yDelta = touch->getDelta().y;
}


void HomeLayer::_preLoadData()
{
	CocosDenshion ::SimpleAudioEngine:: getInstance()->preloadEffect("button.mp3");
	CocosDenshion ::SimpleAudioEngine:: getInstance()->setEffectsVolume( 1.0f);
}

void HomeLayer::showMenu(float dt){ 
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto menuStartBotton = MenuItemImage::create("btn_start_1.png", "btn_start_0.png", CC_CALLBACK_1(HomeLayer::onButtonPress, this));
	menuStartBotton->setPosition(Vec2(_sp->getPosition().x- menuStartBotton->getContentSize().width*1.0,_sp->getPosition().y));
	menuStartBotton->setVisible(false);
	menuStartBotton->setTag(kTagStartBtn);
	auto menu = Menu::create();
	menu->setPosition(Vec2:: ZERO);
	menu->addChild(menuStartBotton);
	addChild(menu,2);
	auto fade = Sequence::create(FadeOut::create(0.0f),CallFunc::create([=]()
	{
		menuStartBotton->setVisible(true);
	})
	,FadeIn::create(3.0f),NULL);  //DelayTime::create(2)
	menuStartBotton->runAction(fade);
}
void HomeLayer::onButtonPress(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
	MenuItemImage* item = (MenuItemImage*) pSender;
	bool runGame = false;
	switch(item->getTag()){
		case kTagStartBtn:
		startGame();
		break;
	}
}
void HomeLayer::startGame()
{
	//Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto moveUp = MoveBy::create(1.0f,Vec2(0,visibleSize.height*1.1f));
	auto hideMenuAction = Sequence::create(moveUp,DelayTime::create(1.0), CallFunc::create([=]()  
	{  
		this->setVisible(false);
	}),NULL);
	this->runAction(hideMenuAction);
}