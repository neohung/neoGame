#include "HudLayer.h"

#define JOYPAD_BG "joystick_bg.png"
#define JOYPAD_THUMB "joystick_thumb.png"
#define JOYPAD_OPACITY 100

#define JOYPAD_SIZE_SCALE 0.5f


HudLayer::HudLayer()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto joypadBG = Sprite::create(JOYPAD_BG);
	joypadBG->setOpacity(JOYPAD_OPACITY);
	joypadBG->setScale(JOYPAD_SIZE_SCALE);
	auto joypadThumb = Sprite::create(JOYPAD_THUMB);
	joypadThumb->setOpacity(JOYPAD_OPACITY);
	joypadThumb->setScale(JOYPAD_SIZE_SCALE);
	_joypad = new NeoJoystick(joypadBG,joypadThumb,Rect(joypadBG->getContentSize().width/2*joypadBG->getScale() + visibleSize.width*0.1f, joypadBG->getContentSize().height/2*joypadBG->getScale() + visibleSize.height*0.1f, joypadBG->getContentSize().width*joypadBG->getScale(), joypadBG->getContentSize().height*joypadBG->getScale()));
	addChild(_joypad);
}

HudLayer::~HudLayer()
{
	
}

void HudLayer::updateControl(HeroSprite* player)
{
	
	Vec2 velocity = _joypad->getVelocity();
	velocity.x *=  player->speed;
	velocity.y *=  player->speed;
	//player->doMove(velocity);
	player->~HeroSprite();

}