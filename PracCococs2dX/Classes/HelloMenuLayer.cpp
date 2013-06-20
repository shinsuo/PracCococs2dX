//
//  HelloMenuLayer.cpp
//  PracCococs2dX
//
//  Created by shin on 13-6-20.
//
//

#include "HelloMenuLayer.h"

using namespace cocos2d;

CCLayer* HelloMenuLayer::layer()
{
    // 'scene' is an autorelease object
    
    // 'layer' is an autorelease object
    HelloMenuLayer *layer = HelloMenuLayer::create();
    
    // return the scene
    return layer;
}

// on "init" you need to initialize your instance
bool HelloMenuLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCMenuItemImage *pCloseItem1 = CCMenuItemImage::create(
                                                          "button_pauseback_01.png",
                                                          "button_pauseback_02.png",
                                                          this,
                                                          menu_selector(HelloMenuLayer::menuCloseCallback) );
    pCloseItem1->setPosition( ccp(0, 50) );
    
    CCMenuItemImage *pCloseItem2 = CCMenuItemImage::create(
                                                           "button_pausecontinue_01.png",
                                                           "button_pausecontinue_02.png",
                                                           this,
                                                           menu_selector(HelloMenuLayer::menuCloseCallback) );
    pCloseItem2->setPosition( ccp(0, -50) );
    
    CCMenu* pMenu = CCMenu::create(pCloseItem1,pCloseItem2, NULL);
    pMenu->alignItemsVertically();
    pMenu->setPosition( ccp(size.width/2,size.height/2) );
    this->addChild(pMenu, 1);
    
    return true;
}

void HelloMenuLayer::onEnter()
{
    CCLog("HelloMenuLayer::onEnter");
    registerWithTouchDispatcher();
}

void HelloMenuLayer::registerWithTouchDispatcher()
{
    CCLog("HelloMenuLayer::registerWithTouchDispatcher");
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, 1);
}


void HelloMenuLayer::menuCloseCallback(CCObject* pSender)
{
    CCLog("HelloMenuLayer::menuCloseCallback");
}