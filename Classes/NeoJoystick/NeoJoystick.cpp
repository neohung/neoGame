#include "NeoJoystick.h"

#define PI 3.14159265359f
#define PI_X_2 6.28318530718f
#define RAD2DEG 180.0f/PI
#define DEG2RAD PI/180.0f

NeoJoystick::NeoJoystick(Sprite* BG, Sprite* Thumb, Rect rect) : _backgroundSprite(BG), _thumbSprite(Thumb), _rect(rect)
{
	addChild(_backgroundSprite);
	addChild(_thumbSprite);
	stickPosition = Vec2::ZERO;
	degrees = 0.0f;
	velocity = Vec2::ZERO;
	joystickRadius = rect.size.width/2; 
	thumbRadius = 32 ;
	deadRadius = 0 ;
	_backgroundSprite->setPosition(_rect.origin);
	_thumbSprite->setPosition(_rect.origin);
	auto touchlistener = EventListenerTouchOneByOne::create(); 
	touchlistener->onTouchBegan = CC_CALLBACK_2(NeoJoystick::onTouchBegan, this); 
	touchlistener->onTouchMoved = CC_CALLBACK_2(NeoJoystick::onTouchMoved, this); 
	touchlistener->onTouchEnded = CC_CALLBACK_2(NeoJoystick::onTouchEnded, this); 
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchlistener, this); 

}

NeoJoystick::~NeoJoystick()
{


}


void NeoJoystick::onEnterTransitionDidFinish()
{
	log("NeoJoystick::onEnterTransitionDidFinish");
	//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
}

float round(float r) {
	return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}

bool NeoJoystick::onTouchBegan(Touch* touch, Event* event){  
	Point pt = this->convertToNodeSpace(touch->getLocation()); 
	_beganPoint = pt;
	//log("NeoJoystick::onTouchBegan(%lf,%lf)",pt.x,pt.y);
	return true;
}

void NeoJoystick::onTouchEnded(Touch* touch, Event* event){  
	Point pt = this->convertToNodeSpace(touch->getLocation());
	//log("NeoJoystick::onTouchEnded(%lf,%lf)",pt.x,pt.y);
	velocity = Vec2::ZERO;
	_beganPoint = _rect.origin;
	_thumbSprite->setPosition(_rect.origin);
}

void NeoJoystick::onTouchMoved(Touch* touch, Event* event){
	Point pt = this->convertToNodeSpace(touch->getLocation());
	//auto xDelta = touch->getDelta().x;
	//auto yDelta = touch->getDelta().y;
	float xDelta = pt.x - _beganPoint.x;
	float yDelta = pt.y - _beganPoint.y;
	
	float angle = atan2f(yDelta, xDelta); // in radians
	if(angle < 0)
	{
		angle		+= PI_X_2;
	}
	float cosAngle;
	float sinAngle;
	cosAngle = cosf(angle);
	sinAngle = sinf(angle);
	//xDelta and yDelta should not greater than joystickRadius
	if ((std::sqrt(std::abs(xDelta)) + std::sqrt(std::abs(yDelta))) > std::sqrt(joystickRadius)) {
		xDelta = cosAngle * joystickRadius;
		yDelta = sinAngle * joystickRadius;
	}
	velocity = Vec2(xDelta/joystickRadius, yDelta/joystickRadius);
	degrees = angle * RAD2DEG;
	_thumbSprite->setPosition(_rect.origin.x+xDelta,_rect.origin.y+yDelta);
}

Vec2 NeoJoystick::getVelocity()
{
	return velocity;
}
