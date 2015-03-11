#ifndef __NEO_JOYSTICK_H__
#define __NEO_JOYSTICK_H__

#include "cocos2d.h"

USING_NS_CC;

class NeoJoystick : public cocos2d::Layer
{
public:
	NeoJoystick(Sprite* BG, Sprite* Thumb, Rect rect);
	virtual ~NeoJoystick();
	void onEnterTransitionDidFinish();
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	Vec2 getVelocity();
private:
protected:
	float joystickRadius;
	float thumbRadius;
	float deadRadius;
	float degrees;
	Vec2 stickPosition;
	Vec2 velocity;
private:
	Sprite* _backgroundSprite;
	Sprite* _thumbSprite;
	Rect _rect;
	Point _beganPoint;
};

#endif
