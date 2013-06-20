

//
//  MainScene.cpp
//  PracCococs2dX
//
//  Created by shin on 13-6-19.
//
//

#include "MainScene.h"
#include "GameScene.h"
#include "HelloCCB.h"

CCScene* MainScene::scene()
{
    CCScene *sc = CCScene::create();
    
    CCNodeLoaderLibrary *ndLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    ndLibrary->registerCCNodeLoader("MainScene", MainSceneLoader::loader());
    CCBReader *ccbReader = new CCBReader(ndLibrary);
    CCNode *node = ccbReader->readNodeGraphFromFile("ccb/MainScene.ccbi");
    ccbReader->release();
    sc->addChild(node);
    return sc;
}

bool MainScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    
    
    return true;
}

void MainScene::start(CCObject *pSender){
    CCLog("start ===");
    CCScene *sc =  GameScene::scene();
    CCDirector::sharedDirector()->replaceScene(sc);
}

void MainScene::guest(CCObject *pSender){
    CCLog("guest ===");
}
