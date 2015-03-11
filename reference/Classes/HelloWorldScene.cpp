#include "HelloWorldScene.h"
#include "GameLayer.h"
using namespace cocos2d;

Scene* HelloWorld::scene()
{
	Scene * scene = NULL;
	do
	{
		// 'scene' is an autorelease object
		scene = Scene::create();
		CC_BREAK_IF(!scene);

		// 'layer' is an autorelease object
		HelloWorld *layer = HelloWorld::create();
		CC_BREAK_IF(!layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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
		CGameLayer *pGameLayer = CGameLayer::create();
		addChild(pGameLayer);

		//initTouch();

		bRet = true;
	} while (0);

	return bRet;
}

void HelloWorld::menuCloseCallback(Object* pSender)
{
	// "close" menu item clicked
	Director::getInstance()->end();
}

//void HelloWorld::initTouch()
//{
//	auto listener1 = EventListenerTouchOneByOne::create();//创建一个触摸监听  
//	listener1->setSwallowTouches(true);//设置是否想下传递触摸  
//	//3.0 后可以直接在touchBegan后添加它的实现代码，而不用特意去写一个touchBegan的函数  
//	listener1->onTouchBegan = [](Touch* touch, Event* event){
//		CCLog("began");
//		return true;
//	};
//	//拖动精灵移动  
//	listener1->onTouchMoved = [](Touch* touch, Event* event){
//		CCLog("moved");
//	};
//	listener1->onTouchEnded = [](Touch* touch, Event* event){
//		CCLog("ended");
//	};
//	//将触摸监听添加到eventDispacher中去  
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
//}