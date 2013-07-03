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


CCArray *gFallingGems = NULL;


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
    
//    CCNodeLoaderLibrary *nodeLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
//    nodeLibrary->registerCCNodeLoader("GameScene", GameSceneLoader::loader());
//    bombCCB = new CCBReader(nodeLibrary);
//    CCNode *node1 = bombCCB->readNodeGraphFromFile("ccb/bomb.ccbi",this);
//    addChild(node1);
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
    CCLog("GameScene::ccTouchBegan");
//    bombCCB->getAnimationManager()->runAnimationsForSequenceNamed("Bomb");
    return true;
}

CCNode* GameScene::addCCB(const char *ccbName)
{
    CCNodeLoaderLibrary *nodeLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    nodeLibrary->registerCCNodeLoader("GameScene", GameSceneLoader::loader());
    CCBReader *ccbReader = new CCBReader(nodeLibrary);
    CCNode *node1 = ccbReader->readNodeGraphFromFile(ccbName,this);
    ccbReader->release();
    return node1;
}


void GameScene::layoutFruit()
{
    CCPoint pt = fruitFlag->getPosition();
    CCPoint anchorPt = fruitFlag->getAnchorPoint();
    CCSize size = fruitFlag->getContentSize();
    CCPoint newPt = ccp(pt.x+(0.5-anchorPt.x)*size.width,pt.y+(0.5-anchorPt.y)*size.height);
    CCLog("layoutFruit ===%f,%f",pt.x,pt.y);
    CCLog("layoutFruit ===%f,%f",newPt.x,newPt.y);
//    fruitFlag->setVisible(1);
    fruitArray = new CCArray(FRUIT_NUM);
//    CCNodeLoaderLibrary *nodeLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
//    nodeLibrary->registerCCNodeLoader("GameScene", GameSceneLoader::loader());
//    CCBReader *ccbReader = new CCBReader(nodeLibrary);
//    CCNode *node1 = addCCB("ccb/fruit0.ccbi");//ccbReader->readNodeGraphFromFile("ccb/fruit0.ccbi",this);
//    CCNode *node2 = addCCB("ccb/fruit1.ccbi");//ccbReader->readNodeGraphFromFile("ccb/fruit1.ccbi",this);
//    CCNode *node3 = ccbReader->readNodeGraphFromFile("ccb/fruit2.ccbi",this);
//    CCNode *node4 = ccbReader->readNodeGraphFromFile("ccb/fruit3.ccbi",this);
//    CCNode *node5 = ccbReader->readNodeGraphFromFile("ccb/fruit4.ccbi",this);
    char ccbName[20];
//    for (int i = 0; i < FRUIT_NUM; i++) {
//        memset(ccbName, 0, sizeof(ccbName));
//        sprintf(ccbName, "ccb/fruit%d",i);
//        fruitArray->addObject(addCCB(ccbName));
//    }

//    CCNode *tSprite= (CCNode *)fruitArray->objectAtIndex(FRUIT_NUM - 1);// fruitArray->objectAtIndex(FRUIT_NUM - 1);//
//    addChild(tSprite);
//    tSprite->setPosition(ccp(2*(FRUIT_WIDTH+1)+pt.x,3*(FRUIT_HEIGHT+1)+pt.y));
//    return;
//    addChild(node1);
////    ccbReader->getAnimationManager()->runAnimationsForSequenceNamed("AnimationScale");
//    node1->setPosition(ccp(2*(FRUIT_WIDTH+1)+pt.x,3*(FRUIT_HEIGHT+1)+pt.y));
    
//    CCArray *allSeq = ccbReader->getAnimationManager()->getSequences();
//    for (int i = 0; i < allSeq->count(); i++) {
//        CCBSequence *everySeq = (CCBSequence *)allSeq->objectAtIndex(i);
//        CCLog("duration:%f",everySeq->getDuration());
//        CCLog("duration:%s",everySeq->getName());
//        CCLog("duration:%d",everySeq->getSequenceId());
//
//    }
    
//    for (int i = 0; i < FRUIT_NUM; i++) {
//        CCNode *node = (CCNode *) fruitArray->objectAtIndex(i);
//        addChild(node);
//        node->setPosition(ccp(0*(FRUIT_WIDTH+1)+pt.x,i*(FRUIT_HEIGHT+1)+pt.y));
//    }
    
//    return;
    gFallingGems = new CCArray(HORIZONTAL_NUM);
    for (int i = 0 ; i < HORIZONTAL_NUM; i++) {
        gFallingGems->insertObject(new CCArray(VERTICAL_NUM),i);
    }
    
    CCLog("gFallingGems:%d",gFallingGems->count());
    
    for (int i = 0; i < HORIZONTAL_NUM; i++) {
        for (int j = 0; j < VERTICAL_NUM; j++) {
//            CCSprite *tSprite = CCSprite::create("icon_02.png");
//            addChild(tSprite);
//            tSprite->setScale(4/3);
//            tSprite->setPosition(ccp(i*(FRUIT_WIDTH+1)+pt.x,j*(FRUIT_HEIGHT+1)+pt.y));
            
            int random = arc4random()%FRUIT_NUM;
            CCLog("random ===%d",random);
            memset(ccbName, 0, sizeof(ccbName));
            sprintf(ccbName, "ccb/fruit%d",random);
            
            CCNode *tSprite=  (CCNode *)addCCB(ccbName);//ccbReader->readNodeGraphFromFile(ccbName,this);//(CCNode *)node1;//
            addChild(tSprite);
            tSprite->setPosition(ccp(i*(FRUIT_WIDTH+1)+newPt.x,j*(FRUIT_HEIGHT+1)+newPt.y));
            ((CCArray *)gFallingGems->objectAtIndex(i))->insertObject(tSprite, j);
        }
    }
}


