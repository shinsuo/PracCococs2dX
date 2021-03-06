

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

#include "Logo.h"

CCScene* MainScene::scene()
{
    CCScene *sc = CCScene::create();
    
    CCNodeLoaderLibrary *ndLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    ndLibrary->registerCCNodeLoader("MainScene", MainSceneLoader::loader());
    CCBReader *ccbReader = new CCBReader(ndLibrary);
    CCNode *node = ccbReader->readNodeGraphFromFile("ccb/MainScene");
    ccbReader->release();
    sc->addChild(node);
    return sc;
}

bool MainScene::init()
{
//    if (!CCLayer::init()) {
//        return false;
//    }
//    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//    CCPoint pt = ccp(winSize.width,winSize.height);
//    
//    ccDrawCircle(pt, 10, 10, 10,1, 2, 2);
    
    
    return true;
}

void MainScene::start(CCObject *pSender){
    CCLog("start ===");
    CCScene *sc =  GameScene::scene();
    CCDirector::sharedDirector()->replaceScene(sc);
}

void MainScene::guest(CCObject *pSender){
//    CCLog("guest ===");
//    CCNode *logo = Logo::node();
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//    logo->setPosition(ccp(winSize.width/2,winSize.height/2+100));
//    addChild(logo);
}
