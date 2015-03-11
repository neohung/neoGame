#ifndef _ACTION_BUTTON_H_
#define _ACTION_BUTTON_H_

#include "cocos2d.h"

USING_NS_CC;

class CHudLayer;	// 由HudLayer代理attackButtonClick(nAttackType)
// 动作按钮
//TouchDelegate
class CActionButton : public Node, public DirectorDelegate

{
public:
	CActionButton();
	virtual ~CActionButton();

	virtual bool init(const char *szImage);
	void click();
	void clickUp();
	virtual bool IsCanClick() { return true;}

	// get & set
	 Rect GetRect();
	int GetAttackType() { return m_nAttackType;}
	
	void SetAttackType(int nAttackType) { m_nAttackType = nAttackType;}
	void SetHudLayer(CHudLayer *pHudLayer) { m_pHudLayer = pHudLayer;}

	void initTouch();

	void updateProjection(void);

protected:
	virtual void onEnter();
	virtual void onExit();

	bool containsTouchLocation( Touch* touch);
	virtual bool ccTouchBegan( Touch* touch,  Event* event);
	virtual void ccTouchMoved( Touch* touch,  Event* event);
	virtual void ccTouchEnded( Touch* touch,  Event* event);

	virtual void beganAnimation() {}
	virtual void endedAnimation() {}

	 Sprite		*m_pSprite;	
	int				m_nAttackType;
	CHudLayer		*m_pHudLayer;
};


// 攻击按钮
// 普通攻击按钮的效果，初始化设置图片素材
class CAttackButton : public CActionButton
{
public:
	~CAttackButton();
	virtual bool init(const char *szImage);
	static CAttackButton* create(const char *szImage);

	virtual bool IsCanClick();

private:
	CAttackButton();

	virtual void beganAnimation();
	virtual void endedAnimation();

	 Sprite		*m_pNormal;

	float			m_fDefaultScale;
	float			m_fMaxScale;
	 Action		*m_pInAction;
	 Action		*m_pOutAction;

	float			m_fClickTime;
};

// 攻击特效
// 特效攻击有个冷却效果，不能在一定时间范围内连续攻击，使用一个 旋转的 Progress 来达到这样的效果
class CAttackEffect : public CActionButton
{
public:
	~CAttackEffect();
	static CAttackEffect* create(const char *szImage);

	virtual bool IsCanClick();
private:
	CAttackEffect();

	virtual void beganAnimation();
	virtual void endedAnimation();
	void endColdTime();

	 ProgressTimer		*m_pNormal;
	 Action			*m_pInAction;
	bool				m_bCanClick;
};

#endif  // _ACTION_BUTTON_H_