#include "GameLayer.h"
#include "HudLayer.h"
#include "Characters.h"

bool CGameLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Layer::init());

		m_szWinSize = Director::sharedDirector()->getWinSize();
		m_ptCenter = ccp(m_szWinSize.width / 2, m_szWinSize.height / 2);

		// Ìí¼Ó±³¾°
		Sprite *pBackGround = Sprite::create("demo/fighting/BackGround.png");
		pBackGround->setPosition(m_ptCenter);
		//addChild(pBackGround);

		// Ìí¼ÓÓ¢ÐÛ
		m_pHero = CHero::create();

		// Ìí¼Ó»úÆ÷ÈË
		m_pRobot = CRobot::create();

		Node *characters = Node::create();
		characters->addChild(m_pHero);
		//characters->addChild(m_pRobot);
		addChild(characters);

		// Ìí¼Ó¿ØÖÆ²ã
		CHudLayer *pHudLayer = CHudLayer::create();
		pHudLayer->setDelegate(this);
		addChild(pHudLayer);

		scheduleUpdate();

		bRet = true; 

	} while (0);
	return bRet;
}

void CGameLayer::update( float delta )
{
	//float z = m_pHero->getZLocation() > m_pRobot->getZLocation() ? 0 : 1;
	//m_pHero->setZOrder(z);
	//m_pRobot->setZOrder(1 - z);
}

void CGameLayer::actionJoypadStart( float degrees )
{
	m_pHero->runWithDegrees(degrees);
	CCLog("------------actionJoypadStart");
}

void CGameLayer::actionJoypadUpdate( float degrees )
{
	m_pHero->moveWithDegrees(degrees);
	CCLog("------------actionJoypadUpdate");
}

void CGameLayer::actionJoypadEnded( float degrees )
{
	m_pHero->idle();
	CCLog("------------actionJoypadEnded");
}

void CGameLayer::attackButtonClick( int nAttackType )
{
	m_pHero->attack(nAttackType);
	CCLog("------------attackButtonClick");
} 