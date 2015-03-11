#include "FightingScene.h"
#include "GameLayer.h"

using namespace cocos2d;

Scene* FightingScene::scene()
{
	Scene * scene = NULL;
	do
	{
		// 'scene' is an autorelease object
		scene = Scene::create();
		CC_BREAK_IF(!scene);

		// 'layer' is an autorelease object
		auto *layer = FightingScene::create();
		CC_BREAK_IF(!layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
} 

// on "init" you need to initialize your instance
bool FightingScene::init()
{
	bool bRet = false;
	do
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(!Layer::init());

		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////
		//CGameLayer *pGameLayer = CGameLayer::create();
		//addChild(pGameLayer);

		//initTouch();

		bRet = true;
	} while (0);

	return bRet;
}

void FightingScene::menuCloseCallback(Object* pSender)
{
	// "close" menu item clicked
	Director::getInstance()->end();
}