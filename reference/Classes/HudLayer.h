#ifndef _HUD_LAYER_H_
#define _HUD_LAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class CGameLayer;
class CJoypad;
class CAttackButton;
class CAttackEffect;

// ������ť����
enum eAttackButtonType
{
	abtNone,
	abtAttack,
	abtAttackA,
	abtAttackB,
	abtAttackMax,
};

// ��������
enum eRoleType
{
	rtHero,
	rtRobot,
};

// ����״̬
class CState : public Node
{
public:
	virtual bool init();
	CREATE_FUNC(CState);

	static CState* createHero();
	static CState* createRobot();
	
	// get & set
	void setBloodSprite(Sprite *pSprite) { m_pBloodSprite = pSprite;}
	void setBlood(int value);
	void setRoleType(int nType) { m_nRoleType = nType;}
private:
	virtual void onEnter();
	virtual void onExit();

	void notifyChangeStatus(Object *pObject);

	Sprite		*m_pBloodSprite;
	int				m_nRoleType;
};

// ����������������ť��һ��ҡ�˿ؼ�
class CHudLayer : public Layer
{
public:	
	~CHudLayer();

	virtual bool init();
	CREATE_FUNC(CHudLayer);

	void attackButtonClick(int nAttackType);

	void keyAttack(int nButtonType);
	void keyAttackUp(int nButtonType);

	// get & set
	void setDelegate(CGameLayer *pGameLayer);

	//void initTouch();
private:
	CHudLayer();

	Size			m_szWinSize;
	Point			m_ptCenter;
	
	CGameLayer		*m_pGameLayer;
	CJoypad			*m_pJoypad;
	CAttackButton	*m_pAttackButton;
	CAttackEffect	*m_pAttackButtonA;
	CAttackEffect	*m_pAttackButtonB;

	CState			*m_pHero;
	CState			*m_pRobot;
};

#endif  // _HUD_LAYER_H_