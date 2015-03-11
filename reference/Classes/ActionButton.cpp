#include "ActionButton.h"
#include "HudLayer.h"

CActionButton::CActionButton()
{
	m_pSprite = NULL;
	m_pHudLayer = NULL;
}

CActionButton::~CActionButton()
{

}

bool CActionButton::init(const char *szImage)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! Node::init());

		m_pSprite =  Sprite::create(szImage);
		addChild(m_pSprite);

		initTouch();

		bRet = true;
	} while (0);
	return bRet;
}

void CActionButton::updateProjection(void)
{
	CCLog("");
}

void CActionButton::click()
{
	if (IsCanClick() && m_pHudLayer)
	{
		m_pHudLayer->attackButtonClick(GetAttackType());
		beganAnimation();
	}
}

void CActionButton::clickUp()
{
	endedAnimation();
}

cocos2d:: Rect CActionButton::GetRect()
{
	 Size size = m_pSprite->getContentSize();
	return  Rect(-size.width/2, -size.height/2, size.width, size.height);
}

void CActionButton::onEnter()
{
	// Director::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
	 Node::onEnter();
}

void CActionButton::onExit()
{
	// Director::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	 Node::onExit();
}

bool CActionButton::containsTouchLocation(  Touch* touch )
{
	return GetRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool CActionButton::ccTouchBegan(  Touch* touch,  Event* event )
{
	CCLog("ccTouchBegan");
	// 区域判断
	if (!this->containsTouchLocation(touch))
		return false;

	// 播放点击动画
	click();

	return true;
}

void CActionButton::ccTouchMoved(  Touch* touch,  Event* event )
{
	CCLog("ccTouchMoved");
}

void CActionButton::ccTouchEnded(  Touch* touch,  Event* event )
{
	CCLog("ccTouchEnded");
	endedAnimation();
}

CAttackButton::CAttackButton()
{
	m_fDefaultScale = 0.35;
	m_fMaxScale = 0.5;

	m_pNormal =  Sprite::create("demo/fighting/AttackO.png");
	m_pNormal->retain();

	 FiniteTimeAction *pScale =  ScaleTo::create(0.1, m_fDefaultScale);
	 FiniteTimeAction *pFadeIn =  FadeIn::create(0.1);
	m_pInAction =  Spawn::create(pScale, pFadeIn, NULL);
	m_pInAction->retain();

	pScale =  ScaleTo::create(0.2f, m_fMaxScale);
	 FiniteTimeAction *pFade =  FadeOut::create(0.2);
	m_pOutAction =  Spawn::create(pScale, pFade, NULL);
	m_pOutAction->retain();

	m_fClickTime = 0.0f;
}

CAttackButton::~CAttackButton()
{
	CC_SAFE_RELEASE(m_pNormal);
	CC_SAFE_RELEASE(m_pInAction);
	CC_SAFE_RELEASE(m_pOutAction);
}

bool CAttackButton::init( const char *szImage )
{
	bool bRet = CActionButton::init(szImage);
	if (m_pNormal)
		m_pNormal->setScale(m_fMaxScale);
	return bRet;
}

CAttackButton* CAttackButton::create( const char *szImage )
{
	//CAttackButton *pAttackButton = new CAttackButton();
	CAttackButton *pAttackButton = new CAttackButton();
	if (pAttackButton && pAttackButton->init(szImage))
	{
		pAttackButton->autorelease();
		return pAttackButton;
	}
	else
	{
		delete pAttackButton;
		return NULL;
	}
}

void CAttackButton::beganAnimation()
{
	removeChild(m_pNormal);
	addChild(m_pNormal);
	m_pNormal->runAction(( Action*)m_pInAction->clone());
	
	timeval timeVal;
	 //CCTime::gettimeofdayCocos2d(&timeVal, 0);
	gettimeofday(&timeVal, 0);
	m_fClickTime = timeVal.tv_sec * 1000 + timeVal.tv_usec / 1000;
}

void CAttackButton::endedAnimation()
{
	m_pNormal->stopAllActions();
	m_pNormal->runAction(( Action*)m_pOutAction->clone());
}

bool CAttackButton::IsCanClick()
{
	timeval timeVal;
	//Time::gettimeofdayCocos2d(&timeVal, 0); 
	gettimeofday(&timeVal, 0);
	float curTime = timeVal.tv_sec * 1000 + timeVal.tv_usec / 1000;
	return (curTime - m_fClickTime > 600);
}

CAttackEffect::CAttackEffect()
{
	 Sprite *pCold =  Sprite::create("demo/fighting/AttackFreeze.png");
	m_pNormal =  ProgressTimer::create(pCold);
	m_pNormal->setType(kCCProgressTimerTypeRadial);
	m_pNormal->setReverseDirection(true);
	m_pNormal->setScale(0.43);
	m_pNormal->retain();

	 FiniteTimeAction *to =  ProgressTo::create(0, 99.999);
	 FiniteTimeAction *to1 =  ProgressTo::create(2, 0);
	 FiniteTimeAction *callback = CCCallFunc::create(this, callfunc_selector(CAttackEffect::endColdTime));
	m_pInAction =  Sequence::create(to, to1, callback, NULL);
	m_pInAction->retain();
	m_bCanClick = true;
}

CAttackEffect::~CAttackEffect()
{
	CC_SAFE_RELEASE(m_pNormal);
	CC_SAFE_RELEASE(m_pInAction);
}


CAttackEffect* CAttackEffect::create( const char *szImage )
{
	CAttackEffect *pAttackEffect = new CAttackEffect();
	if (pAttackEffect && pAttackEffect->init(szImage))
	{
		pAttackEffect->autorelease();
		return pAttackEffect;
	}
	else
	{
		delete pAttackEffect;
		return NULL;
	}
}

void CAttackEffect::beganAnimation()
{
	removeChild(m_pNormal);
	addChild(m_pNormal);
	m_pNormal->runAction(( Action*)m_pInAction->clone());
	m_bCanClick = false;
}

void CAttackEffect::endedAnimation()
{
	
}

bool CAttackEffect::IsCanClick()
{
	return m_bCanClick;
}

void CAttackEffect::endColdTime()
{
	m_bCanClick = true;
}

void CActionButton::initTouch()
{
	CCLog("initTouch");
	auto touchListener = EventListenerTouchOneByOne::create(); 
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(CActionButton::ccTouchBegan,this);
	touchListener->onTouchMoved = CC_CALLBACK_2(CActionButton::ccTouchMoved,this);
	touchListener->onTouchEnded = CC_CALLBACK_2(CActionButton::ccTouchEnded,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}