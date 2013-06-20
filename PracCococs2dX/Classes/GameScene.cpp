//
//  GameScene.cpp
//  PracCococs2dX
//
//  Created by shin on 13-6-19.
//
//

#include "GameScene.h"
#include "PauseLayer.h"

CCScene* GameScene::scene()
{
    CCScene *sc = CCScene::create();
    CCNodeLoaderLibrary *nodeLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    nodeLibrary->registerCCNodeLoader("GameScene", GameSceneLoader::loader());
    CCBReader *ccbReader = new CCBReader(nodeLibrary);
    CCNode *node = ccbReader->readNodeGraphFromFile("ccb/GameScene.ccbi");
    ccbReader->release();
    sc->addChild(node);
    return sc;
}

bool GameScene::init(){
    if (!CCLayer::init()) {
        return false;
    }
    
    
    
    return true;
}

void GameScene::onEnter()
{
    CCLayer::onEnter();
    CCLog("onEnter");
    
}

void GameScene::registerWithTouchDispatcher()
{
    CCLog("registerWithTouchDispatcher");
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,INT_MAX,true);
}

void GameScene::pause(CCObject *pSender)
{
    CCLog("pause ===");
//    CCNodeLoaderLibrary *nodeLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
//    nodeLibrary->registerCCNodeLoader("GameScene", GameSceneLoader::loader());
//    CCBReader *ccbReader = new CCBReader(nodeLibrary);
//    CCLayer *node = (CCLayer *)ccbReader->readNodeGraphFromFile("ccb/PauseLayer.ccbi",this);
    CCLayer *node = PauseLayer::layer();
    addChild(node,INT_MAX,3);
}

void GameScene::resume(CCObject *pSender)
{
    CCLog("resume ===");
    removeChildByTag(3);
}

void GameScene::back(CCObject *pSender)
{
    CCLog("back ===");
}

void GameScene::restart(CCObject *pSender)
{
    CCLog("restart ===");
}