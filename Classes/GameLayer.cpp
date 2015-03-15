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
	_player = new HeroSprite("A1f_4.png","heros/ActorsPack1.png","heros/ActorsPack1.plist",0);
	if (!_player){
		log("fail!");
		return;
	}
	_player->setScale(2);
	_player->setPosition(200,100);
	addChild(_player->spritebatch);
	// Add Move Limit
	Rect limit1 = Rect(origin.x,origin.y,visibleSize.width,visibleSize.height);
	_player->addMoveLimits(limit1);
	Rect limit2 = Rect(origin.x,origin.y+20,visibleSize.width,250);
	_player->addMoveLimits(limit2);
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
	//auto a = hero->hSprite->getActionByTag(111);
	Vec2 velocity = _hudLayer->updateControl(dt);
	if (velocity.x == 0 && velocity.y == 0){
		if (_player->getPositionX() > 300){
			if ( _player->getActionByTag(222) == NULL ){
				_player->stopAllActions();
				auto animate = Animate::create(AnimationCache::getInstance()->getAnimation("heroAttackF"));
				_player->runAction(animate);
				animate->setTag(222);
			}
		}else if (_player->getPositionX() < 100){
			if ( _player->getActionByTag(333) == NULL ){
				_player->stopAllActions();
				auto animate = Animate::create(AnimationCache::getInstance()->getAnimation("heroDeadB"));
				_player->runAction(animate);
				animate->setTag(333);
			}
		}
	}else{
		if ( _player->getActionByTag(111) == NULL ){
			char str[100] = {0};
			if (velocity.x > 0){
				sprintf(str, "heroWalkF");
			}else if(velocity.x < 0){
				sprintf(str, "heroWalkB");
			}
			_player->stopAllActions();
			auto animate = Animate::create(AnimationCache::getInstance()->getAnimation(str));
			_player->runAction(animate);
			animate->setTag(111);
		}
		_player->doMove(dt,velocity);
	}
}