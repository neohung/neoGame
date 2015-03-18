#include "HudLayer.h"
#include "tinyxml2/tinyxml2.h"

#define JOYPAD_BG "joystick_bg.png"
#define JOYPAD_THUMB "joystick_thumb.png"
#define JOYPAD_OPACITY 100

#define JOYPAD_SIZE_SCALE 0.5f


void State::setBlood( float value )
{
	if (value < 0)
		value = 0;
	if (value > 1)
		value = 1;
	if (m_pBloodSprite)
		m_pBloodSprite->setScaleX(value);
}

void setAttrToXML(std::string xmlFileName,std::string parentNodeName,std::string keyPattern,std::string keyVal,std::string attrType,std::string attrVal)
{
	tinyxml2::XMLDocument* pXmlDoc = new tinyxml2::XMLDocument();
	auto xmlContent = CCFileUtils::getInstance()->getDataFromFile(xmlFileName);
	auto ret = pXmlDoc->Parse((const char*)xmlContent.getBytes(), xmlContent.getSize());
	if (ret != 0)
	{
		log("XML File Parse Error!");
		return;
	}
	tinyxml2::XMLElement* xmlRoot = pXmlDoc->RootElement();
	if (!strcmp(xmlRoot->Name(), parentNodeName.c_str())){
		
	}else{
		for (tinyxml2::XMLElement* xmlChild = xmlRoot->FirstChildElement(); xmlChild; xmlChild = xmlChild->NextSiblingElement()) {
			const char* xmlNodeName = xmlChild->Name(); 
			for (tinyxml2::XMLElement* e = xmlChild->FirstChildElement(); e; e = e->NextSiblingElement()) {
				if (!strcmp(xmlNodeName,parentNodeName.c_str()) && !strcmp(e->Name(),keyPattern.c_str()) && !strcmp(e->GetText(),keyVal.c_str())){
					//e->NextSiblingElement()->setText(attrVal.c_str());
					xmlChild->DeleteChild(e->NextSiblingElement());
					xmlChild->DeleteChild(e);
					tinyxml2::XMLElement* keyNode = pXmlDoc->NewElement(keyPattern.c_str());
					tinyxml2::XMLText* kval = pXmlDoc->NewText(keyVal.c_str());
					tinyxml2::XMLElement* typeNode = pXmlDoc->NewElement(attrType.c_str());
					tinyxml2::XMLText* val = pXmlDoc->NewText(attrVal.c_str());
					typeNode->LinkEndChild(val);
					keyNode->LinkEndChild(kval);
					xmlChild->LinkEndChild(keyNode);
					xmlChild->LinkEndChild(typeNode);
				}
			}
		}
	}
	char filepath[256];
	sprintf(filepath,"Resources/%s",xmlFileName.c_str());
	pXmlDoc->SaveFile(filepath);
	delete pXmlDoc;

}

void addAttrToXML(std::string xmlFileName,std::string parentNodeName,std::string keyPattern,std::string keyVal,std::string attrType,std::string attrVal)
{
	tinyxml2::XMLDocument* pXmlDoc = new tinyxml2::XMLDocument();
	auto xmlContent = CCFileUtils::getInstance()->getDataFromFile(xmlFileName);
	auto ret = pXmlDoc->Parse((const char*)xmlContent.getBytes(), xmlContent.getSize());
	if (ret != 0)
	{
		log("XML File Parse Error!");
		return;
	}
	tinyxml2::XMLElement* xmlRoot = pXmlDoc->RootElement();
	if (!strcmp(xmlRoot->Name(), parentNodeName.c_str())){
		tinyxml2::XMLElement* keyNode = pXmlDoc->NewElement(keyPattern.c_str());
		tinyxml2::XMLText* kval = pXmlDoc->NewText(keyVal.c_str());
		tinyxml2::XMLElement* typeNode = pXmlDoc->NewElement(attrType.c_str());
		tinyxml2::XMLText* val = pXmlDoc->NewText(attrVal.c_str());
		typeNode->LinkEndChild(val);
		keyNode->LinkEndChild(kval);
		xmlRoot->LinkEndChild(keyNode);
		xmlRoot->LinkEndChild(typeNode);
	}else{
		for (tinyxml2::XMLElement* xmlChild = xmlRoot->FirstChildElement(); xmlChild; xmlChild = xmlChild->NextSiblingElement()) {
			if (!strcmp(xmlChild->Name(), parentNodeName.c_str())){
				tinyxml2::XMLElement* keyNode = pXmlDoc->NewElement(keyPattern.c_str());
				tinyxml2::XMLText* kval = pXmlDoc->NewText(keyVal.c_str());
				tinyxml2::XMLElement* typeNode = pXmlDoc->NewElement(attrType.c_str());
				tinyxml2::XMLText* val = pXmlDoc->NewText(attrVal.c_str());
				typeNode->LinkEndChild(val);
				keyNode->LinkEndChild(kval);
				xmlChild->LinkEndChild(keyNode);
				xmlChild->LinkEndChild(typeNode);
			}
		}
	}
	char filepath[256];
	sprintf(filepath,"Resources/%s",xmlFileName.c_str());
	pXmlDoc->SaveFile(filepath);
	delete pXmlDoc;
}

void addNodeToXML(std::string xmlFileName,std::string parentNodeName,std::string nodeName)
{
	tinyxml2::XMLDocument* pXmlDoc = new tinyxml2::XMLDocument();
	auto xmlContent = CCFileUtils::getInstance()->getDataFromFile(xmlFileName);
	auto ret = pXmlDoc->Parse((const char*)xmlContent.getBytes(), xmlContent.getSize());
	if (ret != 0)
	{
		log("XML File Parse Error!");
		return;
	}
	tinyxml2::XMLElement* xmlRoot = pXmlDoc->RootElement();
	if (!strcmp(xmlRoot->Name(), parentNodeName.c_str())){
		tinyxml2::XMLElement* newNode = pXmlDoc->NewElement(nodeName.c_str());
		xmlRoot->LinkEndChild(newNode);
	}else{
		for (tinyxml2::XMLElement* xmlChild = xmlRoot->FirstChildElement(); xmlChild; xmlChild = xmlChild->NextSiblingElement()) {
			if (!strcmp(xmlChild->Name(), parentNodeName.c_str())){
				tinyxml2::XMLElement* newNode = pXmlDoc->NewElement(nodeName.c_str());
				xmlChild->LinkEndChild(newNode);
			}
		}
	}
	char filepath[256];
	sprintf(filepath,"Resources/%s",xmlFileName.c_str());

	pXmlDoc->SaveFile(filepath);
	delete pXmlDoc;
}
void createXML(std::string xmlFileName,std::string descript,std::string rootNodeName)
{
	tinyxml2::XMLDocument* pXmlDoc = new tinyxml2::XMLDocument();
	tinyxml2::XMLDeclaration* declare = pXmlDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
	pXmlDoc->LinkEndChild(declare); 
	tinyxml2::XMLComment* comment = pXmlDoc->NewComment(descript.c_str());
	pXmlDoc->LinkEndChild(comment);
	tinyxml2::XMLElement* root = pXmlDoc->NewElement(rootNodeName.c_str());
	root->SetAttribute("id", "neo");
	pXmlDoc->InsertEndChild(root);
	char filepath[256];
	sprintf(filepath,"Resources/%s",xmlFileName.c_str());
	pXmlDoc->SaveFile(filepath);
	delete pXmlDoc;
}

void* readXML(std::string xmlFileName,std::string nodeName, std::string attrName)
{
	const int max_char_size = 256;
	void* val = NULL;
	const std::string keyPattern = "key";
	tinyxml2::XMLDocument* pXmlDoc = new tinyxml2::XMLDocument();
	auto xmlContent = CCFileUtils::getInstance()->getDataFromFile(xmlFileName);
	auto ret = pXmlDoc->Parse((const char*)xmlContent.getBytes(), xmlContent.getSize());
	if (ret != 0)
	{
		log("XML File Parse Error!");
		return NULL;
	}
	tinyxml2::XMLElement* xmlRoot = pXmlDoc->RootElement();
	//log("root : %s", xmlRoot->Name());	 // should be "plist"	
	for (tinyxml2::XMLElement* xmlChild = xmlRoot->FirstChildElement(); xmlChild; xmlChild = xmlChild->NextSiblingElement()) {
		const char* xmlNodeName = xmlChild->Name(); //would be "player_name" and "player_hp"
		//log("xmlChild : %s", xmlNodeName);
		for (tinyxml2::XMLElement* e = xmlChild->FirstChildElement(); e; e = e->NextSiblingElement()) {
			if (!strcmp(xmlNodeName,nodeName.c_str()) && !strcmp(e->Name(),keyPattern.c_str()) && !strcmp(e->GetText(),attrName.c_str())){
				if (!strcmp(e->NextSiblingElement()->Name(), "string")){
					val = (char*)malloc(max_char_size);
					sprintf((char*)val,"%s",e->NextSiblingElement()->GetText());
				}else if (!strcmp(e->NextSiblingElement()->Name(), "int")){
					int* pTmp = (int*) malloc(sizeof(int));
					*pTmp = atoi(e->NextSiblingElement()->GetText());
					val = pTmp;
				}else if (!strcmp(e->NextSiblingElement()->Name(), "float")){
					float* pTmp = (float*) malloc(sizeof(float));
					*pTmp = atof(e->NextSiblingElement()->GetText());
					//log("conv [%s] to %lf",e->NextSiblingElement()->GetText(),tmp);
					val = pTmp;
				}
				//log("N %s,%s",e->NextSiblingElement()->Name(), e->NextSiblingElement()->GetText() );
			}
			//log("e : %s , %s", e->Name(), e->GetText());
		}
	}
	delete pXmlDoc;
	return val;
}

State* State::createHero()
{
	State* pState = (State*)State::create();
	if (pState){
		auto pSprite1 = Sprite::create("heros/HeroState1.png");
		auto pSprite2 = Sprite::create("heros/HeroState2.png");
		auto pSprite3 = Sprite::create("heros/HeroState3.png");
		auto pSprite4 = Sprite::create("heros/HeroState4.png");

		pSprite1->setPosition(pSprite1->getContentSize().width/2+5, -pSprite1->getContentSize().height/2-5);

		pSprite2->setPosition(75, -pSprite2->getContentSize().height-25);
		pSprite2->setAnchorPoint(Vec2(0, 0));
		pSprite3->setPosition(75, -pSprite3->getContentSize().height-35);
		pSprite3->setAnchorPoint(Vec2(0, 0));
		pState->setBloodSprite(pSprite3);

		pSprite4->setPosition(0, 0);
		pSprite4->setAnchorPoint(Vec2(0, 1));

		pState->addChild(pSprite2);
		pState->addChild(pSprite1);
		pState->addChild(pSprite3);
		pState->addChild(pSprite4);

		char* playerName = (char*)readXML("names.xml","player_name","people1");
		float* pVal = (float*)readXML("names.xml","player_hp","people1");
		if(pVal){
			log("set blood %f",*pVal);
			pState->setBlood(*pVal);
		}
		if (playerName){
			auto pTitle = LabelTTF::create(playerName, "Tahoma", 14);
			pTitle->setPosition(90,-5);
			pTitle->setAnchorPoint(Vec2(0, 1));
			pState->addChild(pTitle);
		}
	}
	return pState;
}


HudLayer::HudLayer()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//------------------------------JOYPAD---------------------------------------
	auto joypadBG = Sprite::create(JOYPAD_BG);
	joypadBG->setOpacity(JOYPAD_OPACITY);
	//joypadBG->setScale(JOYPAD_SIZE_SCALE);
	auto joypadThumb = Sprite::create(JOYPAD_THUMB);
	joypadThumb->setOpacity(JOYPAD_OPACITY);
	//joypadThumb->setScale(JOYPAD_SIZE_SCALE);
	_joypad = new NeoJoystick(joypadBG,joypadThumb,Rect(joypadBG->getContentSize().width/2*joypadBG->getScale() + visibleSize.width*0.1f, joypadBG->getContentSize().height/2*joypadBG->getScale() + visibleSize.height*0.1f, joypadBG->getContentSize().width*joypadBG->getScale(), joypadBG->getContentSize().height*joypadBG->getScale()));
	addChild(_joypad);
	//----------------------------------------------------------------------------
	State* pHeroState = State::createHero();
	pHeroState->setPosition(0, visibleSize.height);
	addChild(pHeroState);

}

HudLayer::~HudLayer()
{

}

Vec2 HudLayer::updateControl(float dt)
{
	return _joypad->getVelocity();
	//Vec2 velocity = _joypad->getVelocity();
	//velocity.x *=  player->speed;
	//velocity.y *=  player->speed;
	//player->doMove(dt,velocity);
}