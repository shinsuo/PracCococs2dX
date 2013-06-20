//
//  GameScene.cpp
//  PracCococs2dX
//
//  Created by shin on 13-6-19.
//
//

#include "GameScene.h"
#include "PauseLayer.h"

#define HORIZONTAL_NUM  7
#define VERTICAL_NUM    7
#define FRUIT_WIDTH     85
#define FRUIT_HEIGHT    85
#define FRUIT_NUM       5

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
    
    setTouchEnabled(1);
    
    
    return true;
}

void GameScene::onEnter()
{
    CCLayer::onEnter();
    CCLog("GameScene::onEnter");
    pauseMenu->setHandlerPriority(10);
    
    layoutFruit();
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
    addChild(node,3,3);
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


bool GameScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}


void GameScene::layoutFruit()
{
    CCPoint pt = fruitFlag->getPosition();
    fruitFlag->setVisible(1);
    fruitArray = new CCArray(FRUIT_NUM);
    CCNodeLoaderLibrary *nodeLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    nodeLibrary->registerCCNodeLoader("GameScene", GameSceneLoader::loader());
    CCBReader *ccbReader = new CCBReader(nodeLibrary);
    CCNode *node1 = ccbReader->readNodeGraphFromFile("ccb/fruit0.ccbi",this);
    CCNode *node2 = ccbReader->readNodeGraphFromFile("ccb/fruit1.ccbi",this);
    CCNode *node3 = ccbReader->readNodeGraphFromFile("ccb/fruit2.ccbi",this);
    CCNode *node4 = ccbReader->readNodeGraphFromFile("ccb/fruit3.ccbi",this);
    CCNode *node5 = ccbReader->readNodeGraphFromFile("ccb/fruit4.ccbi",this);
    
    char ccbName[20];

//    CCNode *tSprite= (CCNode *)fruitArray->objectAtIndex(FRUIT_NUM - 1);// fruitArray->objectAtIndex(FRUIT_NUM - 1);//
//    addChild(tSprite);
//    tSprite->setPosition(ccp(2*(FRUIT_WIDTH+1)+pt.x,3*(FRUIT_HEIGHT+1)+pt.y));
//    return;
    
    for (int i = 0; i < HORIZONTAL_NUM; i++) {
        for (int j = 0; j < VERTICAL_NUM; j++) {
//            CCSprite *tSprite = CCSprite::create("icon_02.png");
//            addChild(tSprite);
//            tSprite->setScale(4/3);
//            tSprite->setPosition(ccp(i*(FRUIT_WIDTH+1)+pt.x,j*(FRUIT_HEIGHT+1)+pt.y));

            int random = arc4random()%FRUIT_NUM;
            memset(ccbName, 0, sizeof(ccbName));
            sprintf(ccbName, "ccb/fruit%d.ccbi",random);
            CCLog("%s",ccbName);
            return;
            CCNode *tSprite=  (CCNode *)ccbReader->readNodeGraphFromFile(ccbName,this);//(CCNode *)node1;//
            addChild(tSprite);
            tSprite->setPosition(ccp(i*(FRUIT_WIDTH+1)+pt.x,j*(FRUIT_HEIGHT+1)+pt.y));
        }
    }
}


