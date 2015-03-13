#include "GameLayer.h"
#include "HeroSprite.h"

GameLayer::GameLayer(HudLayer* hudLayer): _hudLayer(hudLayer)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	log("visibleSize: %lfx%lf",visibleSize.width,visibleSize.height);
	srand(time(0));
	//NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameLayer::pauseGame), NOTIFICATION_PAUSE_GAME, nullptr);
	_initMap();
	//Layer includ Score, Time, Label items in GameLayer
	_initLayer();
}

GameLayer::~GameLayer()
{
	//NotificationCenter::getInstance()->removeObserver(this, NOTIFICATION_PAUSE_GAME);
	
}

void GameLayer::configureGame(int gamelevel)
{
	_initElements();
	_initPlayer();
	runGame();
}

void GameLayer::_initMap()
{
	auto bg0 = Sprite::create("bg0.png");
	bg0->setAnchorPoint(Vec2::ZERO);
	auto bg1 = Sprite::create("bg1.png");
	bg1->setAnchorPoint(Vec2::ZERO);
	bg1->setPositionX(bg0->getContentSize().width);
	addChild(bg0);
	addChild(bg1);
}

void GameLayer::_initElements()
{

}

void GameLayer::_initLayer()
{
}

void GameLayer::_initPlayer()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	HeroSprite* Sprite1 = new HeroSprite("A1_0.png","heros/ActorsPack1.png","heros/ActorsPack1.plist",0);
	if (!Sprite1){
		log("fail!");
		return;
	}
	_player = Sprite1;

	Sprite1->setScale(2);
	Sprite1->setPosition(200,100);
	addChild(Sprite1->spritebatch);

	char str[100] = {0};
	for(int i = 1; i < 9; i++) 
	{
		sprintf(str, "A1f_%01d.png", i);
		Sprite1->addAnimFrames(str);
	}
	// Add Move Limit
	Sprite1->runAction( RepeatForever::create(Sprite1->createAnimate(0.3f)));
	Rect limit1 = Rect(origin.x,origin.y,visibleSize.width,visibleSize.height);
	Sprite1->addMoveLimits(limit1);
	Rect limit2 = Rect(origin.x,origin.y+20,visibleSize.width,250);
	Sprite1->addMoveLimits(limit2);
}

void GameLayer::update(float dt)
{
	_gameLogic(dt);
}

void GameLayer::runGame()
{
	log("GameLayer::runGame()");
	this->unscheduleUpdate(); 
	this->scheduleUpdate();
}

void GameLayer::onEnterTransitionDidFinish()
{
	log("GameLayer::onEnterTransitionDidFinish()");
	//runGame();
}

void GameLayer::_gameLogic(float dt)
{
	_hudLayer->updateControl(_player,dt);
}