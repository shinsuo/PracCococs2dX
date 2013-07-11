//
//  GameScene.cpp
//  PracCococs2dX
//
//  Created by shin on 13-6-19.
//
//

#include "GameScene.h"
#include "PauseLayer.h"
#include "FruitObject.h"
#include <vector>

#define HORIZONTAL_NUM  7
#define VERTICAL_NUM    7
#define FRUIT_WIDTH     85
#define FRUIT_HEIGHT    85
#define FRUIT_NUM       5

CCArray *gFallingGems = NULL;
std::vector<FruitObject *> g_VfruitObjects;
CCPoint markPos;

#pragma ----Common Function----

std::vector<Index> g_Veliminate;

bool isValidIndex(Index index)
{
    if (index.i < HORIZONTAL_NUM
        && (index.i >= 0)
        && (index.j < VERTICAL_NUM)
        && (index.j >= 0)
        ) {
        return true;
    }
    return false;
}

Index getIndexByPoint(const CCPoint pt)
{
    Index index = {-1,-1};
    float i = (pt.x - (markPos.x - FRUIT_WIDTH/2))/(FRUIT_WIDTH+1);
    float j = (pt.y - (markPos.y - FRUIT_HEIGHT/2))/(FRUIT_HEIGHT+1);
//    CCLog("getIndexByPoint 1===%f,%f,%f,%f",pt.x,(markPos.x - FRUIT_WIDTH/2),(pt.x - (markPos.x - FRUIT_WIDTH/2)),(pt.x - (markPos.x - FRUIT_WIDTH/2))/(FRUIT_WIDTH+1));
    if ((i < HORIZONTAL_NUM)
        && (i >= 0)
        && (j < VERTICAL_NUM)
        && (j >= 0)) {
        index.i = i;
        index.j = j;
//        CCLog("getIndexByPoint 2==%d,%d",i,j);
    }
    return index;
}

FruitObject* getFruitByIndex(Index index)
{
    FruitObject * fruit = (FruitObject *)((CCArray *)gFallingGems->objectAtIndex(index.i))->objectAtIndex(index.j);
    return fruit;
}

void getEliminateArray(Index index,const unsigned int color)
{
    
//    Index *eliminateArray = new Index[1];
//    eliminateArray[0].i  = index.i;
//    eliminateArray[0].j  = index.j;
//    return eliminateArray;
    FruitObject *touchFruit = getFruitByIndex(index);
    if ((touchFruit->color == color)
        && (touchFruit->choose == false)
        
        ) {
        g_Veliminate.push_back(index);
        touchFruit->choose = true;
        
        //expand to all around
        //to left
        Index left = {index.i-1,index.j};
        if (isValidIndex(left)) {
            getEliminateArray(left,color);
        }
        
        //to right
        Index right = {index.i+1,index.j};
        if (isValidIndex(right)) {
            getEliminateArray(right,color);
        }
        
        //to down
        Index down = {index.i,index.j-1};
        if (isValidIndex(down)) {
            getEliminateArray(down,color);
        }
        
        //to top
        Index top = {index.i,index.j+1};
        if (isValidIndex(top)) {
            getEliminateArray(top,color);
        }
    }
    
    
//    return g_Veliminate;
}



#pragma ----Common Function----

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
//    if (!CCLayer::init()) {
//        return false;
//    }
//
    
    CCLog("size_t vs int  ===%d,%d",sizeof(size_t),sizeof(int));
    setTouchEnabled(1);
    
    
    return true;
}

void GameScene::onEnter()
{
    CCLayer::onEnter();
    CCLog("GameScene::onEnter");
    pauseMenu->setHandlerPriority(10);
    afterloadCCB();
    layoutFruit();
    
//    CCNodeLoaderLibrary *nodeLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
//    nodeLibrary->registerCCNodeLoader("GameScene", GameSceneLoader::loader());
//    bombCCB = new CCBReader(nodeLibrary);
//    CCNode *node1 = bombCCB->readNodeGraphFromFile("ccb/bomb.ccbi",this);
//    addChild(node1);
//    
//    bombCCB->getAnimationManager()->setAnimationCompletedCallback(this, callfunc_selector(GameScene::removeBomb));
//    
//    CCSize size = CCDirector::sharedDirector()->getWinSize();
//    node1->setPosition(ccp(size.width/2,size.height/2));
}

void GameScene::afterloadCCB()
{
    CCPoint pt = fruitFlag->getPosition();
    CCPoint anchorPt = fruitFlag->getAnchorPoint();
    CCSize size = fruitFlag->getContentSize();
    markPos = ccp(pt.x+(0.5-anchorPt.x)*size.width,pt.y+(0.5-anchorPt.y)*size.height);
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
    CCPoint pt =  pTouch->getLocation();
//    CCLog("GameScene::ccTouchBegan ===%f,%f",pt.x,pt.y);
    Index tempIndex = getIndexByPoint(pt);
    CCLog("tempIndex ==%d,%d",tempIndex.i,tempIndex.j);
    FruitObject *touchFruit =  (FruitObject *)((CCArray *)gFallingGems->objectAtIndex(tempIndex.i))->objectAtIndex(tempIndex.j);
    getEliminateArray(tempIndex,touchFruit->color);
    
    if (g_Veliminate.size() >= 3) {
        for (std::vector<Index>::iterator it = g_Veliminate.begin(); it != g_Veliminate.end(); it++) {
            CCLog("loop ===%d,%d",it->i,it->j);
            removeFruit(*it);
        }
    }
    
    
    
//    CCLog("vector size:%d,%d",g_Veliminate.size(),g_Veliminate.capacity());
//    g_Veliminate.clear();
    std::vector<Index>().swap(g_Veliminate);
//    CCLog("vector size:%d,%d",g_Veliminate.size(),g_Veliminate.capacity());

//    CCLog("getEliminateArray == %d,%d",v_eliminate[0].i,v_eliminate[0].j);
    
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

FruitObject* GameScene::fallingObject(unsigned int color)
{
    char ccbName[20];
    memset(ccbName, 0, sizeof(ccbName));
    sprintf(ccbName, "ccb/fruit%d",color);
    
    FruitObject *tSprite=  (FruitObject *)addCCB(ccbName);//ccbReader->readNodeGraphFromFile(ccbName,this);//(CCNode *)node1;//
    addChild(tSprite);
//    tSprite->setTag(i*FRUIT_WIDTH+j);
    tSprite->color = color;
    tSprite->choose = false;
//    tSprite->setPosition(ccp(i*(FRUIT_WIDTH+1)+newPt.x,j*(FRUIT_HEIGHT+1)+newPt.y));
//    ((CCArray *)gFallingGems->objectAtIndex(i))->insertObject(tSprite, j);
    return tSprite;
//    return NULL;
}

void GameScene::removeFruit(Index index)
{
    CCNode *node =  getChildByTag(index.i*FRUIT_WIDTH+index.j);
    CCPoint pt = node->getPosition();
    node->removeFromParent();
    
    CCNode *node1 =  addCCB("ccb/bomb");
    addChild(node1);
    node1->setPosition(pt);
    
    
    ((CCArray *)gFallingGems->objectAtIndex(index.i))->objectAtIndex(index.j);
}

void GameScene::layoutFruit()
{
    CCPoint pt = fruitFlag->getPosition();
    CCPoint anchorPt = fruitFlag->getAnchorPoint();
    CCSize size = fruitFlag->getContentSize();
    CCPoint newPt = ccp(pt.x+(0.5-anchorPt.x)*size.width,pt.y+(0.5-anchorPt.y)*size.height);
    CCLog("layoutFruit ===%f,%f",pt.x,pt.y);
    CCLog("layoutFruit ===%f,%f",newPt.x,newPt.y);
    markPos = CCPoint(newPt.x,newPt.y);
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
//            CCLog("random ===%d",random);
//            memset(ccbName, 0, sizeof(ccbName));
//            sprintf(ccbName, "ccb/fruit%d",random);
//            
//            FruitObject *tSprite=  (FruitObject *)addCCB(ccbName);//ccbReader->readNodeGraphFromFile(ccbName,this);//(CCNode *)node1;//
//            addChild(tSprite);
            
            FruitObject *tSprite = fallingObject(random);
            
            tSprite->setTag(i*FRUIT_WIDTH+j);
            tSprite->setPosition(ccp(i*(FRUIT_WIDTH+1)+newPt.x,j*(FRUIT_HEIGHT+1)+newPt.y));
            ((CCArray *)gFallingGems->objectAtIndex(i))->insertObject(tSprite, j);
        }
    }
}


void GameScene::removeBomb()
{
    
}


