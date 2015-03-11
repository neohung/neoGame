#ifndef _JOYPAD_H_
#define _JOYPAD_H_

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class CGameLayer;	// 由CGameLayer代理actionJoypadStart/Update/Ended
// 摇杆
// 其实质是在ccTouchBegan等响应事件中调用CCGameLayer的代理，更好的做法这里不是直接用CGameLayer
// 而是将CGameLayer中的这些代理函数写到一个接口中，然后让CGameLayer继承，这里用那个接口类即可
class CJoypad : public  Layer
{
public:
	~CJoypad();

	virtual bool init();
	CREATE_FUNC(CJoypad);

	void keyStart(float degrees);
	void keyUpdate(float degrees);
	void keyEnded(float degrees);

	void setGameLayer(CGameLayer* pGameLayer) { m_pGameLayer = pGameLayer; }
private:
	CJoypad();

	virtual void onEnter();
	virtual void onExit();

	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	// cocos2dx2.x
	// bool ccTouchBegan( Touch* touch,  Event* event);
	// void ccTouchMoved(Touch* touch, Event* event);
	// void ccTouchEnded( Touch* touch,  Event* event);
	// cocos2dx3.X
	//void onTouchesBegan(const vector<Touch*>& touches, Event* event);
	//void onTouchEnded(const vector<Touch*>& touches, Event* event);
	//void onTouchMoved(const vector<Touch*>& touches, Event* event);

	inline void UpdateRotation();
	inline void UpdateTouchRotation(Touch* touch, Event* event);

	Size		m_szWinSize;
	Point		m_ptCenter;
	Sprite	*m_pControlSprite;
	Point		m_ptDefaultPoint;

	float		m_fDefaultRotation;
	float		m_fRotation;

	CGameLayer	*m_pGameLayer;
	bool		m_bKeydown;

	void initTouch();
};


#endif  // _ACTION_BUTTON_H_