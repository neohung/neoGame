#ifndef __HUDLAYER_H__
#define __HUDLAYER_H__

#include "cocos2d.h"
#include "HeroSprite.h"
#include "NeoJoystick/NeoJoystick.h"

using namespace cocos2d;

class State : public Node{
public:
	static State* createHero();
	void setBlood(float value);
	void setBloodSprite(Sprite* blood_sp)  { m_pBloodSprite = blood_sp;}
private:
private:
		Sprite* m_pBloodSprite;
};

class HudLayer : public Layer{
public:
	HudLayer();
	~HudLayer();
	Vec2 updateControl(float dt);
private:
private:
	NeoJoystick* _joypad;
};

#endif