#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "HudLayer.h"
#include "HeroSprite.h"

using namespace cocos2d;

typedef struct _HERO
{
	HeroSprite* hSprite;
	Animate * playerAttackAnimate;
	Animate * playerWalkAnimate;
	Animate * playerDeadAnimate;
	Animate * fplayerAttackAnimate;
	Animate * fplayerWalkAnimate;
	Animate * fplayerDeadAnimate;
}HERO;

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
	HERO* hero;
	HudLayer* _hudLayer;
	HeroSprite* _player;
	Animate * _playerAttackAnimate;
	Animate * _playerWalkAnimate;
	Animate * _playerDeadAnimate;
};

#endif