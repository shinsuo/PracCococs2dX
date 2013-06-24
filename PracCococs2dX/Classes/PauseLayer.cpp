//
//  PauseLayer.cpp
//  PracCococs2dX
//
//  Created by shin on 13-6-20.
//
//

#include "PauseLayer.h"

CCLayer* PauseLayer::layer()
{
    CCNodeLoaderLibrary *nodeLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    nodeLibrary->registerCCNodeLoader("PauseLayer", PauseLayerLoader::loader());
    CCBReader *ccbReader = new CCBReader(nodeLibrary);
    CCLayer *node = (CCLayer*)ccbReader->readNodeGraphFromFile("ccb/PauseLayer.ccbi");
    ccbReader->release();
    return node;
}

bool PauseLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    setTouchEnabled(1);
    return true;
}

void PauseLayer::onEnter()
{
    CCLayer::onEnter();
    CCLog("PauseLayer::onEnter");
//    pauseLayerMenu->setHandlerPriority(0);
}

void PauseLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, 1);
    CCLog("PauseLayer::registerWithTouchDispatcher===%d",__INT_MAX__);
}

void PauseLayer::resume(CCObject *pSender)
{
    CCLog("resume ===");
    removeFromParent();
}

void PauseLayer::back(CCObject *pSender)
{
    CCLog("back ===");
}

void PauseLayer::restart(CCObject *pSender)
{
    CCLog("restart ===");
}

bool PauseLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}
