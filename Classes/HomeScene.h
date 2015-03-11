#ifndef __HOMESCENE_H__
#define __HOMESCENE_H__

#include "cocos2d.h"


using namespace cocos2d;

enum
{
    kZHomeLayer = 99999,
    kZHudLayer = 9999,
    kZGameLayer = 999
};

#define DESIGN_RESOLUTION_480X320    0
#define DESIGN_RESOLUTION_1024X768   1
#define DESIGN_RESOLUTION_2048X1536  2
#define TARGET_DESIGN_RESOLUTION_SIZE  DESIGN_RESOLUTION_480X320

typedef struct tagResource
{
    cocos2d :: Size size;       
    char directory[100]; 
}Resource;
 
static Resource smallResource  =   { cocos2d ::Size( 480 , 320 ),   "480x320" };    //iphone
static Resource mediumResource =   { cocos2d ::Size( 1024 , 768 ),  "1024x768"   };  // ipad
static Resource largeResource  =   { cocos2d ::Size( 2048 , 1536 ), "2048x1536" };      //ipadhd
 
#if (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_480X320)
static cocos2d:: Size designResolutionSize = cocos2d :: Size(480 , 320);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_1024X768)
static cocos2d:: Size designResolutionSize = cocos2d :: Size(1024 , 768);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_2048X1536)
static cocos2d:: Size designResolutionSize = cocos2d :: Size(2048 , 1536);
#else
#error unknown target design resolution!
#endif

class HomeScene: public Layer
{
public:
	//Appdelegate.cpp會調用到這createScene()
	static Scene* createScene();
	//CREATE_FUNC會建立HomeScene::create()並在裡面調用HomeScene::init()
	virtual bool init();
	CREATE_FUNC(HomeScene);
private:
private:
};
#endif