#include "HudLayer.h"
#include "GameLayer.h"
#include "Joypad.h"
#include "ActionButton.h"
#include "Characters.h"

bool CState::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Node::init());		
		bRet = true;
	} while (0);
	return bRet;
}

void CState::setBlood( int value )
{
	if (value < 0)
		value = 0;
	if (value > 1)
		value = 1;
	if (m_pBloodSprite)
		m_pBloodSprite->setScaleX(value);
}

CState* CState::createHero()
{
	CState *pState = CState::create();
	if (pState)
	{
		Sprite *pSprite1 = Sprite::create("demo/fighting/HeroState1.png");
		Sprite *pSprite2 = Sprite::create("demo/fighting/HeroState2.png");
		Sprite *pSprite3 = Sprite::create("demo/fighting/HeroState3.png");
		Sprite *pSprite4 = Sprite::create("demo/fighting/HeroState4.png");

		pSprite1->setPosition(ccp(-80, 3));
		pSprite2->setPosition(ccp(33, 15));
		
		pSprite3->setPosition(ccp(-45, -12));
		pSprite3->setAnchorPoint(ccp(0, 0));
		pState->setBloodSprite(pSprite3);

		pState->addChild(pSprite1);
		pState->addChild(pSprite2);
		pState->addChild(pSprite3);
		pState->addChild(pSprite4);
		pState->setRoleType(rtHero);

		Dictionary *pDict = Dictionary::createWithContentsOfFile("demo/fighting/names.xml");
		String *pStr = dynamic_cast<String*>(pDict->objectForKey("people2"));
		if (pStr)
		{
			LabelTTF *pTitle = LabelTTF::create(pStr->getCString(), "Tahoma", 14);
			pTitle->setPosition(ccp(-15, 30));
			pState->addChild(pTitle);
		}
	}

	return pState;
}

CState* CState::createRobot()
{
	CState *pState = CState::create();
	if (pState)
	{
		Sprite *pSprite1 = Sprite::create("demo/fighting/RobotState1.png");
		Sprite *pSprite2 = Sprite::create("demo/fighting/RobotState2.png");
		Sprite *pSprite3 = Sprite::create("demo/fighting/RobotState3.png");
		Sprite *pSprite4 = Sprite::create("demo/fighting/RobotState4.png");

		pSprite1->setPosition(ccp(50, -16));
		pState->setBloodSprite(pSprite1);
		pSprite1->setAnchorPoint(ccp(1, 0));

		pSprite2->setPosition(ccp(-20, -7));
		pSprite4->setPosition(ccp(65, 1));

		pState->addChild(pSprite2);
		pState->addChild(pSprite1);
		pState->addChild(pSprite3);
		pState->addChild(pSprite4);
		pState->setRoleType(rtRobot);
		
		 Dictionary *pDict =  Dictionary::createWithContentsOfFile("demo/fighting/names.xml");
		 String *pStr = dynamic_cast< String*>(pDict->objectForKey("people1"));
		if (pStr)
		{
			 LabelTTF *pTitle =  LabelTTF::create(pStr->getCString(), "Tahoma", 14);
			pTitle->setPosition(ccp(-15, 12));
			pState->addChild(pTitle);
		}
	}

	return pState;
}

void CState::onEnter()
{
	 Node::onEnter();
	 NotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CState::notifyChangeStatus), "status", NULL);
}

void CState::onExit()
{
	 NotificationCenter::sharedNotificationCenter()->removeObserver(this, "status");
	 Node::onExit();
}

void CState::notifyChangeStatus(  Object *pObject )
{
	CActionSprite *pActionSprite = (CActionSprite*)pObject;
	if (pActionSprite && pActionSprite->getRoleType() == m_nRoleType)
	{
		setBlood(pActionSprite->getBloodPercent());
	}
}

CHudLayer::CHudLayer()
{
	m_szWinSize =  Director::sharedDirector()->getWinSize();
	m_ptCenter = ccp(m_szWinSize.width/2, m_szWinSize.height/2);
}

CHudLayer::~CHudLayer()
{

}

bool CHudLayer::init()
{
	bool bRet = false;
	do 
	{
		// 添加控制器
		m_pJoypad = CJoypad::create();
		addChild(m_pJoypad);

		// 添加攻击按钮
		m_pAttackButton = CAttackButton::create("demo/fighting/Attack.png");
		m_pAttackButton->setPosition(ccp(m_szWinSize.width - 80, 80));
		m_pAttackButton->SetHudLayer(this);
		m_pAttackButton->SetAttackType(abtAttack);
		addChild(m_pAttackButton);

		// 其他攻击
		m_pAttackButtonA = CAttackEffect::create("demo/fighting/AttackA.png");
		m_pAttackButtonA->setPosition(ccp(m_szWinSize.width - 200, 60));
		m_pAttackButtonA->SetHudLayer(this);
		m_pAttackButtonA->SetAttackType(abtAttackA);
		//addChild(m_pAttackButtonA);

		m_pAttackButtonB = CAttackEffect::create("demo/fighting/AttackB.png");
		m_pAttackButtonB->setPosition(ccp(m_szWinSize.width - 165, 165));
		m_pAttackButtonB->SetHudLayer(this);
		m_pAttackButtonB->SetAttackType(abtAttackB);
		//addChild(m_pAttackButtonB);

		// 添加 Hero 血条状态
		m_pHero = CState::createHero();
		m_pHero->setPosition(ccp(130, m_szWinSize.height - 55));
		//addChild(m_pHero);

		// 怪物血条
		m_pRobot = CState::createRobot();
		m_pRobot->setPosition(ccp(800 - 100, m_szWinSize.height - 35));
		addChild(m_pRobot);

		// test
		//initTouch();

		bRet = true;
	} while (0);
	return bRet;
}

void CHudLayer::attackButtonClick( int nAttackType )
{
	CCLog("  attackButtonClick");
	if (m_pGameLayer)
		m_pGameLayer->attackButtonClick(nAttackType);
}

void CHudLayer::keyAttack( int nButtonType )
{
	if (nButtonType == abtAttack && m_pAttackButton->IsCanClick())
	{
		CCLog("abtAttack ---");
		m_pAttackButton->click();
	}
	else if (nButtonType == abtAttackA && m_pAttackButtonA->IsCanClick())
	{
		CCLog("abtAttack a---");
		m_pAttackButtonA->click();
	}
	else if (nButtonType == abtAttackB && m_pAttackButtonB->IsCanClick())
	{
		CCLog("abtAttack b---");
		m_pAttackButtonB->click();
	}
}

void CHudLayer::keyAttackUp( int nButtonType )
{
	if (nButtonType == abtAttack)
	{
		m_pAttackButton->clickUp();
	}
}

void CHudLayer::setDelegate( CGameLayer *pGameLayer )
{
	m_pGameLayer = pGameLayer;
	m_pJoypad->setGameLayer(pGameLayer);
}

//void CHudLayer::initTouch()
//{
//	CCLog("test touch");
//	auto touchListener = EventListenerTouchOneByOne::create();
//	touchListener->setSwallowTouches(true);
//	//touchListener->onTouchBegan = CC_CALLBACK_2(CJoypad::onTouchBegan, this);
//	touchListener->onTouchBegan = [](Touch* touch, Event* event){
//		CCLog("began");
//		return true;
//	};
//	//touchListener->onTouchMoved = CC_CALLBACK_2(CJoypad::onTouchMoved, this);
//	//touchListener->onTouchEnded = CC_CALLBACK_2(CJoypad::onTouchEnded, this);
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
//	//this->setTouchEnabled(true);
//}
