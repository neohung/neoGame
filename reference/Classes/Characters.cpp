#include "Characters.h"
#include "HudLayer.h"
#include "cocostudio\CocoStudio.h"

//#pragma comment(lib,"pthreadVCE2.lib")  
//#pragma comment(lib,"libchipmunk.lib")  
//#pragma comment(lib,"libExtensions.lib")  

using namespace cocostudio;


CActionSprite::CActionSprite()
{
	m_pSprite = NULL;
	m_bIsRun = false;
	m_fRunDegrees = 0;
	m_fSpeed = 300;

	m_pActionStand = NULL;
	m_pActionRunning = NULL;
	m_pActionAttack = NULL;
	m_pActionAttackJump = NULL;
	m_pActionAttackT = NULL;

	m_fZLocation = 0;
	m_bFlipX = false;
	m_bImageFlipX = false;
	m_fAttackRange = 150;

	m_fBlood = 100;
	m_fBloodMax = 100;
}

CActionSprite::~CActionSprite()
{
	CC_SAFE_RELEASE(m_pActionStand);
	CC_SAFE_RELEASE(m_pActionRunning);
	CC_SAFE_RELEASE(m_pActionAttack);
	CC_SAFE_RELEASE(m_pActionAttackJump);
	CC_SAFE_RELEASE(m_pActionAttackT);
}

bool CActionSprite::init()
{
	bool bRet = false;
	do 
	{
		m_pLossBlood = NULL;
		scheduleUpdate();
		
		bRet = true;
	} while (0);
	return bRet;
}

void CActionSprite::update( float delta )
{
	// 打斗时是不能够跑动的
	if (m_bIsRun && !isAttack())
	{
		float x = sinf(m_fRunDegrees * 2 * M_PI / 360) * m_fSpeed * delta;
		float y = cosf(m_fRunDegrees * 2 * M_PI / 360) * m_fSpeed * delta;

		 Point p = ccp(-y, x);
		if (y < 0)
		{
			if (!m_bFlipX)
				m_pSprite->runAction( ScaleTo::create(0, (m_bImageFlipX ? 1 : -1), 1));

			m_bFlipX = true;
		}
		if (y > 0)
		{
			if (m_bFlipX)
				m_pSprite->runAction( ScaleTo::create(0, (m_bImageFlipX ? -1 : 1), 1));
			m_bFlipX = false;
		}
		setPosition(ccpSub(getPosition(), p));
	}

	checkLocation();
	ai();	
}

void CActionSprite::acceptAttack(  Object* pObject )
{
	if (this != pObject)
	{
		CActionSprite *pActionSprite = (CActionSprite*)pObject;
		// 同一水平高度
		if (fabs(getZLocation() - pActionSprite->getZLocation()) < 30)
		{
			CCLOG("accept attack..%f", pActionSprite->m_fAttackRange);

			// 距离
			float value = getPositionX() - pActionSprite->getPositionX();
			if (!pActionSprite->isFlip() && value >= 0 && value < pActionSprite->m_fAttackRange)
			{
				blood();
			}
			else if (pActionSprite->isFlip() && value <= 0 && -value < pActionSprite->m_fAttackRange)
			{
				blood();
			}
		}
	}
}

void CActionSprite::runWithDegrees( float degrees )
{
	m_bIsRun = true;
	m_fRunDegrees = degrees;
	hRunning();
}

void CActionSprite::hRunning()
{
	m_pSprite->stopAllActions();
	//m_pSprite->runAction(( Action *)m_pActionRunning->copy());
	//m_pSprite->runAction(m_pActionRunning);
	m_pSprite->runAction((Action *)m_pActionRunning->clone());
	m_nState = csRunning;
}

void CActionSprite::moveWithDegrees( float degrees )
{
	m_fRunDegrees = degrees;
}

void CActionSprite::idle()
{
	m_bIsRun = false;
	if (!isAttack())
		hStand();
}

void CActionSprite::hStand()
{
	m_pSprite->stopAllActions();
	m_pSprite->runAction(( Action *)m_pActionStand->clone());
	m_nState = csStand;
}

void CActionSprite::checkLocation()
{
	 Size szWinSize =  Director::sharedDirector()->getWinSize();
	 Point curPoint = getPosition();
	 Point newPoint = getPosition();
	if (curPoint.x < 60)
		newPoint.x = 60;
	if (curPoint.y < 120)
		newPoint.y = 120;
	if (curPoint.x > szWinSize.width - 60)
		newPoint.x = szWinSize.width - 60;
	if (curPoint.y > szWinSize.height / 2 + 80)
		newPoint.y = szWinSize.height / 2 + 80;
	setPosition(newPoint);
}

void CActionSprite::postAttack()
{
	setAttackRect();
	 NotificationCenter::sharedNotificationCenter()->postNotification("attack", this);
}

void CActionSprite::setSprite( const char *szImage, const  Point &pos )
{
	m_pSprite =  Sprite::create(szImage);
	addChild(m_pSprite);
	setPosition(pos);
}

void CActionSprite::setAttackRect()
{
	 Point point = getPosition();
	float fAttackWidth = 100;
	 Point newPoint = m_bFlipX ? ccpSub(point, ccp(100, 0)) : point;
	//_attackRect = cc.rect(point.x - 100 * 2, point.y, 100, 5);
}

void CActionSprite::onEnter()
{
	 Node::onEnter();
	 NotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CActionSprite::acceptAttack), "attack", NULL);
}

void CActionSprite::onExit()
{
	 NotificationCenter::sharedNotificationCenter()->removeObserver(this, "attack");
	 Node::onExit();
}

void CActionSprite::blood()
{
	float lb = 30;
	m_fBlood -= lb;
	removeChild(m_pLossBlood);
	char temp[20];
	sprintf(temp, "-%.f", lb);
	m_pLossBlood =  LabelTTF::create(temp, "Tahoma", 20);
	m_pLossBlood->setPosition(ccp(0, -m_fZLocation));
	addChild(m_pLossBlood);

	 FiniteTimeAction *fadeIn =  FadeIn::create(0.8);
	 FiniteTimeAction *fadeOut =  FadeOut::create(1);
	 FiniteTimeAction *mu =  MoveTo::create(1, ccp(0, 30 + (-m_fZLocation)));
	 Action *action =  Spawn::create(fadeIn, fadeOut, mu, NULL);
	m_pLossBlood->runAction(action);

	// 控制掉血，发送一个掉血的消息
	 NotificationCenter::sharedNotificationCenter()->postNotification("status", this);
}


bool CHero::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CActionSprite::init());

		setSprite("demo/fighting/Hero1.png", ccp(300, 300));
		setZLocation(-80);
		initAction();
		hStand();
		setRoleType(rtHero);

		bRet = true;

		//////////////
		// test

		//FiniteTimeAction		*m_pActionStand;
		//FiniteTimeAction		*m_pActionRunning;
		//FiniteTimeAction		*m_pActionAttack;
		//FiniteTimeAction		*m_pActionAttackJump;
		//FiniteTimeAction		*m_pActionAttackT;

		//m_pSprite->runAction(m_pActionAttackT);

	} while (0);
	return bRet;
}

void CHero::initAction()
{
	// 站立动作
	 Animation *pAnimStand =  Animation::create();
	char szFile[50] = {0};
	for (int i = 1; i <= 3; ++i)
	{
		sprintf(szFile, "demo/fighting/Hero%d.png", i);
		pAnimStand->addSpriteFrameWithFileName(szFile);
	}
	pAnimStand->setDelayPerUnit(5.8 / 14);
	pAnimStand->setRestoreOriginalFrame(true);	// 动画完了返回原始帧
	m_pActionStand = ( FiniteTimeAction *) RepeatForever::create( Animate::create(pAnimStand));
	m_pActionStand->retain();

	// 跑步动作
	 Animation *pAnimRun =  Animation::create();
	for (int i = 1; i <= 11; ++i)
	{
		sprintf(szFile, "demo/fighting/HeroRun%d.png", i);
		pAnimRun->addSpriteFrameWithFileName(szFile);
	}
	pAnimRun->setDelayPerUnit(2.8 / 14);
	pAnimRun->setRestoreOriginalFrame(true);
	m_pActionRunning = ( FiniteTimeAction *) RepeatForever::create( Animate::create(pAnimRun));
	m_pActionRunning->retain();

	// 普通攻击
	 Animation *pAttackNormal =  Animation::create();
	for (int i = 1; i <= 5; ++i)
	{
		sprintf(szFile, "demo/fighting/HeroAttack%d.png", i);
		pAttackNormal->addSpriteFrameWithFileName(szFile);
	}
	pAttackNormal->setDelayPerUnit(1.8 / 14);
	m_pActionAttack =  Animate::create(pAttackNormal);
	m_pActionAttack->retain();

	// 跳跃攻击
	 Animation *pAttackJump =  Animation::create();
	for (int i = 1; i <= 8; ++i)
	{
		sprintf(szFile, "demo/fighting/HeroAttackJ%d.png", i);
		pAttackJump->addSpriteFrameWithFileName(szFile);
	}
	pAttackJump->setDelayPerUnit(0.1);
	m_pActionAttackJump =  Animate::create(pAttackJump);
	m_pActionAttackJump->retain();

	// 突刺攻击
	 Animation *pAttackSpur =  Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		sprintf(szFile, "demo/fighting/HeroAttackT%d.png", i);
		pAttackSpur->addSpriteFrameWithFileName(szFile);
	}
	pAttackSpur->setDelayPerUnit(0.1);
	m_pActionAttackT =  Animate::create(pAttackSpur);
	m_pActionAttackT->retain();
}

void CHero::hAttack(int nAttackType)
{
	 FiniteTimeAction *pAction = NULL;
	switch (nAttackType)
	{
	case abtAttack:
		{
			pAction = m_pActionAttack;
			m_fAttackRange = 150;
		}
		break;
	case abtAttackA:
		{
			pAction = m_pActionAttackJump;
			// 当前位置跳跃
			 Action *jump =  JumpTo::create(0.6, ccpSub(getPosition(), ccp(m_bFlipX ? 200: -200, 0)), 120, 1);
			runAction(jump);
			m_fAttackRange = 300;
		}
		break;
	case abtAttackB:
		{
			pAction = m_pActionAttackT;
			// 当前位置移动
			 Action *move =  MoveTo::create(0.3, ccpSub(getPosition(), ccp(
				m_bFlipX ? 200 : -200, 0)));
			runAction(move);
			m_fAttackRange = 300;
		}
		break;
	}

	if (pAction)
	{
		m_pSprite->stopAllActions();
		 Action *pActions =  Sequence::create(pAction,  CallFunc::create(this, callfunc_selector(CHero::attackEnded)), NULL);
		m_pSprite->runAction(pActions);
		m_nState = csAttack;
		postAttack();
	}
}

void CHero::attack(int nAttackType)
{
	hAttack(nAttackType);
}

void CHero::attackEnded()
{
	if (m_bIsRun)
		hRunning();
	else
		hStand();
}


bool CRobot::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CActionSprite::init());
		
		ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("demo/fighting/armature/NewProject0.png",
			"demo/fighting/armature/NewProject0.plist", "demo/fighting/armature/NewProject.json");
		Armature *pArmature =  Armature::create("NewProject");

		setSprite(pArmature, ccp(500, 300));
		setZLocation(-90);
		hStand();

		runWithDegrees(180);
		setRoleType(rtRobot);
		m_bImageFlipX = true;
		m_fSpeed = 150;

		timeval timeVal;
		gettimeofday(&timeVal, 0);
		m_fStartTime = timeVal.tv_sec * 1000 + timeVal.tv_usec / 1000;

		bRet = true;
	} while (0);
	return bRet;
}

void CRobot::setSprite(  Node *pArmature, const  Point &pos )
{
	m_pSprite = pArmature;
	addChild(m_pSprite);
	setPosition(pos);
}

void CRobot::attack()
{
	hAttack();
}

void CRobot::hAttack()
{
	m_fAttackRange = 150;
	Armature *pArmature = ( Armature*)m_pSprite;
	pArmature->stopAllActions();
	pArmature->getAnimation()->play("attack");
	pArmature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CRobot::attackEnded));
	m_nState = csAttack;
	postAttack();
}

void CRobot::hStand()
{
	 Armature *pArmature = ( Armature*)m_pSprite;
	pArmature->getAnimation()->play("stand");
	m_nState = csStand;
}

void CRobot::hRunning()
{
	 Armature *pArmature = ( Armature*)m_pSprite;
	pArmature->getAnimation()->play("run");
	m_nState = csRunning;
}

void CRobot::attackEnded(  Armature *pArmature, MovementEventType movementType, const char *movementID )
{
	if (movementType == LOOP_COMPLETE)
	{
		if (m_bIsRun)
		{
			hRunning();
		}
		else
		{
			hStand();
		}
	}
}

void CRobot::ai()
{
	static int attackIndex = 0;
	static int moveIndex = 0;

	timeval timeVal;
	gettimeofday(&timeVal, 0);
	float curTime = timeVal.tv_sec * 1000 + timeVal.tv_usec / 1000;
	float value = curTime - m_fStartTime;

	if (moveIndex < value / 3000)
	{
		moveIndex ++;
		float r = CCRANDOM_0_1() * 360;
		moveWithDegrees(r);
	}
	if (attackIndex < value / 6000)
	{
		attackIndex += 1;
		attack();
	}
}


