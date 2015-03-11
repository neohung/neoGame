#include "AppDelegate.h"
#include "HomeScene.h"
//#include "HelloWorldScene.h"

#include "SimpleAudioEngine.h"

//USING_NS_CC;
using namespace cocos2d;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        //螢幕大小,手機是固定無法設定的
        glview->setFrameSize(854,480);
        //glview->setFrameSize(600,600);
        director->setOpenGLView(glview);
    }
///////////////////////////////////////////////
    std::vector<std::string> searchPaths;
    //求出銀幕大小
    auto screenSize = glview->getFrameSize(); 
    if (screenSize.height > mediumResource.size.height)
    {
        //銀幕高大於中尺寸的圖,採用大尺寸圖並用大尺寸圖縮放
        searchPaths.push_back(largeResource.directory);
        director->setContentScaleFactor(largeResource.size.height/designResolutionSize.height);
    }else if (screenSize.height > smallResource.size.height)
    {
        //銀幕高大於小尺寸的圖,採用中尺寸圖並用中尺寸圖縮放
        searchPaths.push_back(mediumResource.directory);
        director->setContentScaleFactor(mediumResource.size.height/designResolutionSize.height); 
    }else
    {
        searchPaths.push_back(smallResource.directory);
        director->setContentScaleFactor(smallResource.size.height/designResolutionSize.height);
    }
    //Director::getInstance()->getOpenGLView()->setDesignResolutionSize(designResolutionSize.width,designResolutionSize.height,ResolutionPolicy::FIXED_HEIGHT);  
   Director::getInstance()->getOpenGLView()->setDesignResolutionSize(designResolutionSize.width,designResolutionSize.height,ResolutionPolicy::SHOW_ALL);  
/*
    searchPaths.push_back("audio");
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BG_MUSIC_01);     
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BG_MUSIC_02);     
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BG_MUSIC_03);     
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.2f);

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SFX_BUTTON);
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
//    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BG_MUSIC_03, true);
*/
///////////////////////////////////////////////
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //auto scene = HelloWorld::createScene();
    auto scene = HomeScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
