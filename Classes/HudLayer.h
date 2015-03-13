#ifndef __HUDLAYER_H__
#define __HUDLAYER_H__

#include "cocos2d.h"
#include "HeroSprite.h"
#include "NeoJoystick/NeoJoystick.h"

using namespace cocos2d;

class HudLayer : public Layer{
public:
	HudLayer();
	~HudLayer();
	void updateControl(HeroSprite* player, float dt);
private:
private:
	NeoJoystick* _joypad;
};

#endif