#include "HomeScene.h"
#include "HomeLayer.h"
#include "GameLayer.h"
#include "HudLayer.h"

Scene* HomeScene::createScene()
{
	auto scene = Scene::create();
	auto layer = HomeScene::create();
	scene->addChild(layer);
	return scene;
}

bool HomeScene::init()
{
	HudLayer* hudLayer = new HudLayer();
	//hudLayer->autorelease();
	addChild(hudLayer, kZHudLayer);
	GameLayer* gameLayer = new GameLayer(hudLayer);
    //gameLayer->autorelease();
    addChild(gameLayer, kZGameLayer);
    HomeLayer* homeLayer = new HomeLayer(gameLayer);
    addChild(homeLayer, kZHomeLayer);
	return true;
}