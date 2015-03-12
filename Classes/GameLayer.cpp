#include "GameLayer.h"
#include "HeroSprite.h"

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
	SpriteBatchNode* spritebatch = SpriteBatchNode::create("heros/ActorsPack1.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("heros/ActorsPack1.plist");
	auto Sprite1 = Sprite::createWithSpriteFrameName("A1f_0.png");
	Sprite1->setScale(2);
	//HeroSprite* Sprite1 = new HeroSprite("A1_0.png");
	//HeroSprite* Sprite1 = new HeroSprite();
	Sprite1->setPosition(200,100);
	spritebatch->addChild(Sprite1,10);
	addChild(spritebatch);

	Vector<SpriteFrame*> animFrames(9);

	char str[100] = {0};
	for(int i = 1; i < 9; i++) 
	{
		sprintf(str, "A1f_%01d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName( str );
		animFrames.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
	Sprite1->runAction( RepeatForever::create( Animate::create(animation) ) );


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