#include "JoyPad.h"
#include "GameLayer.h"


CJoypad::CJoypad()
{
	m_szWinSize = Director::sharedDirector()->getWinSize();
	m_ptCenter = ccp(m_szWinSize.width / 2, m_szWinSize.height / 2);
	m_pControlSprite = NULL;
	m_fDefaultRotation = m_fRotation = 0.0f;

	m_pGameLayer = NULL;
	m_bKeydown = false;
}

CJoypad::~CJoypad()
{

}

bool CJoypad::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		// 控制杆所在位置
		m_ptDefaultPoint = ccp(110, 110);
		// 默认旋转角度，以使开口正对右侧
		m_fDefaultRotation = 26;
		// 实际旋转角度
		m_fRotation = 0;

		setPosition(m_ptDefaultPoint);

		// 添加显示精灵
		addChild(Sprite::create("demo/fighting/Joypad1.png"));
		addChild(Sprite::create("demo/fighting/Joypad2.png"));
		m_pControlSprite = Sprite::create("demo/fighting/Joypad3.png");
		addChild(m_pControlSprite);
		addChild(Sprite::create("demo/fighting/Joypad4.png"));

		UpdateRotation();

		// 事件处理
		initTouch();

		bRet = true;
	} while (0);

	return bRet;
}

void CJoypad::keyStart(float degrees)
{
	if (m_pGameLayer)
		m_pGameLayer->actionJoypadStart(m_fRotation);
}

void CJoypad::keyUpdate(float degrees)
{
	m_fRotation = degrees;
	UpdateRotation();
	if (m_pGameLayer)
		m_pGameLayer->actionJoypadUpdate(m_fRotation);
}

void CJoypad::keyEnded(float degrees)
{
	if (m_pGameLayer)
		m_pGameLayer->actionJoypadEnded(m_fRotation);
}

void CJoypad::onEnter()
{
	Layer::onEnter();
	// TODO
	//Director::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void CJoypad::onExit()
{

}

//void CJoypad::onTouchesBegan(const vector<Touch*>& touches, Event* event)
bool CJoypad::onTouchBegan(Touch* touch, Event* event)
{
	CCLog("======= began");

	Point location = touch->getLocation();

	// 点击点的范围判断
	Point curPoint = touch->getLocation();
	if (curPoint.x > m_szWinSize.width / 2 || curPoint.y > m_szWinSize.height / 2)
		return false;

	UpdateTouchRotation(touch, event);
	UpdateRotation();

	CCAssert(m_pGameLayer, "m_pGameLayer is null");
	if (m_pGameLayer)
		m_pGameLayer->actionJoypadStart(m_fRotation);
	return true;
}

//void CJoypad::onTouchMoved(const vector<Touch*>&touches, Event* event)
void CJoypad::onTouchMoved(Touch* touch, Event* event)
{
	CCLog("======= moved");
	Point location = touch->getLocation();

	UpdateTouchRotation(touch, event);
	UpdateRotation();

	CCAssert(m_pGameLayer, "m_pGameLayer is null");
	if (m_pGameLayer)
		m_pGameLayer->actionJoypadUpdate(m_fRotation);
}

//void CJoypad::onTouchEnded(const vector<Touch*>&touches, Event* event)
void CJoypad::onTouchEnded(Touch* touch, Event* event)
{
	CCLog("======= ended");
	Point location = touch->getLocation();

	UpdateTouchRotation(touch, event);
	UpdateRotation();

	CCAssert(m_pGameLayer, "m_pGameLayer is null");
	if (m_pGameLayer)
		m_pGameLayer->actionJoypadEnded(m_fRotation);
}

void CJoypad::UpdateRotation()
{
	m_pControlSprite->setRotation(m_fDefaultRotation + m_fRotation);
}

void CJoypad::UpdateTouchRotation(Touch* touch, Event* event)
{
	CCLog("touch rotation");
	Point curPoint = touch->getLocation();
	Point sp = ccpSub(curPoint, m_ptDefaultPoint);
	float angle = ccpToAngle(sp);
	angle *= -57.29577951;			// ...
	angle = (angle < 0) ? 360 + angle : angle;
	m_fRotation = angle;
}

void CJoypad::initTouch()
{
	CCLog("test touch");
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(CJoypad::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(CJoypad::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(CJoypad::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}