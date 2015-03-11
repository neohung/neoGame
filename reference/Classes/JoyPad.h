#ifndef _JOYPAD_H_
#define _JOYPAD_H_

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class CGameLayer;	// ��CGameLayer����actionJoypadStart/Update/Ended
// ҡ��
// ��ʵ������ccTouchBegan����Ӧ�¼��е���CCGameLayer�Ĵ������õ��������ﲻ��ֱ����CGameLayer
// ���ǽ�CGameLayer�е���Щ������д��һ���ӿ��У�Ȼ����CGameLayer�̳У��������Ǹ��ӿ��༴��
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