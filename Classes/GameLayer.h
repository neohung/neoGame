#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "HudLayer.h"

using namespace cocos2d;

class GameLayer : public Layer{
public:
	GameLayer(HudLayer* hudLayer);
	~GameLayer();
	void update(float dt);
	void runGame();
	void configureGame(int gamelevel);
	void onEnterTransitionDidFinish();
private:
	void _initMap();
	void _initElements();
	void _initLayer();
	void _initPlayer();
	void _gameLogic(float dt);
private:
};

#endif