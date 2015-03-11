#include "GameLayer.h"

GameLayer::GameLayer(HudLayer* hudLayer)
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
}

void GameLayer::update(float dt)
{
	_gameLogic(dt);
}

void GameLayer::runGame()
{
	log("GameLayer::runGame()");
}

void GameLayer::onEnterTransitionDidFinish()
{
	log("GameLayer::onEnterTransitionDidFinish()");
	runGame();
}

void GameLayer::_gameLogic(float dt)
{
	//_hudLayer->updateControl(*_player);
}