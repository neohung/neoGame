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
	_initEnemy();
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
	_player = new HeroSprite("Hero11f_4.png","heros/ActorsPack1.png","heros/ActorsPack1.plist",0);
	if (!_player){
		log("fail!");
		return;
	}
	_player->initAnimation("Hero11");
	_player->setScale(2);
	_player->setPosition(200,100);
	addChild(_player->spritebatch);
	// Add Move Limit
	Rect limit1 = Rect(origin.x,origin.y,visibleSize.width,visibleSize.height);
	_player->addMoveLimits(limit1);
	Rect limit2 = Rect(origin.x,origin.y+20,visibleSize.width,250);
	_player->addMoveLimits(limit2);
}

void GameLayer::_initEnemy()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_enemy = new Vector<HeroSprite*>();
	HeroSprite* e1 = new HeroSprite("A1f_4.png","heros/ActorsPack1.png","heros/ActorsPack1.plist",0);
	e1->initAnimation("A1");
	e1->setScale(2);
	e1->setPosition(300,100);
	addChild(e1->spritebatch);
	Rect limit1 = Rect(origin.x,origin.y,visibleSize.width,visibleSize.height);
	e1->addMoveLimits(limit1);
	Rect limit2 = Rect(origin.x,origin.y+20,visibleSize.width,250);
	e1->addMoveLimits(limit2);
	_enemy->pushBack(e1);

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
	Map<float, HeroSprite*> zorder_map;  
	// update enemy
	for(int i;i<_enemy->size();i++)
	{
		HeroSprite* e = _enemy->at(i);
		int signx = ((float)rand() / (RAND_MAX)) > 0.5 ? -1:1;
		int signy = ((float)rand() / (RAND_MAX)) > 0.5 ? -1:1;
		float vx= ((float)rand() / (RAND_MAX));
		float vy= ((float)rand() / (RAND_MAX));
		if ( e->getActionByTag(111) == NULL ){
			char str[100] = {0};
			if (signx > 0){
				sprintf(str, "%s_WalkF",e->animationPrefixName.c_str());
			}else {
				sprintf(str, "%s_WalkB",e->animationPrefixName.c_str());
			}
			e->stopAllActions();
			auto animate = Animate::create(AnimationCache::getInstance()->getAnimation(str));
			e->runAction(animate);
			animate->setTag(111);
		}
		//log("%lf,%lf",signx*vx,signy*vy);
		e->doMove(dt,Vec2(signx*vx,signy*vy));
		//e->setLocalZOrder(20000); 
	}

	//auto a = hero->hSprite->getActionByTag(111);
	Vec2 velocity = _hudLayer->updateControl(dt);
	if (velocity.x == 0 && velocity.y == 0){
		if (_player->getPositionX() > 300){
			if ( _player->getActionByTag(222) == NULL ){
				_player->stopAllActions();
				auto animate = Animate::create(AnimationCache::getInstance()->getAnimation("Hero11_AttackF"));
				_player->runAction(animate);
				animate->setTag(222);
			}
		}else if (_player->getPositionX() < 100){
			if ( _player->getActionByTag(333) == NULL ){
				_player->stopAllActions();
				auto animate = Animate::create(AnimationCache::getInstance()->getAnimation("Hero11_DeadB"));
				_player->runAction(animate);
				animate->setTag(333);
			}
		}
	}else{
		if ( _player->getActionByTag(111) == NULL ){
			char str[100] = {0};
			if (velocity.x > 0){
				sprintf(str, "%s_WalkF",_player->animationPrefixName.c_str());
			}else if(velocity.x < 0){
				sprintf(str, "%s_WalkB",_player->animationPrefixName.c_str());
			}
			_player->stopAllActions();
			auto animate = Animate::create(AnimationCache::getInstance()->getAnimation(str));
			_player->runAction(animate);
			animate->setTag(111);
		}
		_player->doMove(dt,velocity); 
	}
	//zorder_map.clear();
		//_player->setLocalZOrder(-20000);
	//reorder
	zorder_map.insert(_player->getPositionY(),_player);
	for(int i;i<_enemy->size();i++)
	{
		HeroSprite* e = _enemy->at(i);
		zorder_map.insert(e->getPositionY(),e);
	}

	std::vector<float> mapKeyVec;
	mapKeyVec = zorder_map.keys();
	int i =0;
	for(auto key : mapKeyVec)
	{
		i++;
		auto sp = zorder_map.at(key);
    	//auto parent = sp->getParent();
    	//parent->reorderChild(sp->spritebatch,i);
		this->reorderChild(sp->spritebatch,i);
    	//sp->getParent()->reorderChild(sp,i);
    	//log("%d->Y:%lf",sp->spritebatch->getLocalZOrder(),sp->getPositionY());
	}
	//log("------");
	zorder_map.clear();
	//_player->spritebatch->setLocalZOrder(1000);
	//log("y=%lf & Z=%d",_player->getPositionY(), _player->spritebatch->getLocalZOrder());
}