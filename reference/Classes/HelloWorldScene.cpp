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
//	auto listener1 = EventListenerTouchOneByOne::create();//����һ����������  
//	listener1->setSwallowTouches(true);//�����Ƿ����´��ݴ���  
//	//3.0 �����ֱ����touchBegan���������ʵ�ִ��룬����������ȥдһ��touchBegan�ĺ���  
//	listener1->onTouchBegan = [](Touch* touch, Event* event){
//		CCLog("began");
//		return true;
//	};
//	//�϶������ƶ�  
//	listener1->onTouchMoved = [](Touch* touch, Event* event){
//		CCLog("moved");
//	};
//	listener1->onTouchEnded = [](Touch* touch, Event* event){
//		CCLog("ended");
//	};
//	//������������ӵ�eventDispacher��ȥ  
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
//}