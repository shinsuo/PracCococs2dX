//
//  PracCococs2dXAppDelegate.cpp
//  PracCococs2dX
//
//  Created by shin on 13-6-7.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "HelloCCB.h"
#include "MainScene.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
//    CCScene *pScene = CCScene::create();//HelloCCB::scene();
//    CCNodeLoaderLibrary *nodeLoader = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
//    nodeLoader->registerCCNodeLoader("HelloCCB", HelloCCBLoader::loader());
//    CCBReader *ccbReader = new CCBReader(nodeLoader);
//    CCNode *node = ccbReader->readNodeGraphFromFile("HelloCocosBuilder.ccbi");
    // run
    CCScene *pScene = HelloWorld::scene();//MainScene::scene(); //
    pDirector->runWithScene(pScene);
//    pScene->addChild(node);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
