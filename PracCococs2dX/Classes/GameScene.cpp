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
#include "Bomb.h"

#include <vector>
#include <algorithm>

#define HORIZONTAL_NUM  7
#define VERTICAL_NUM    7
#define FRUIT_WIDTH     85
#define FRUIT_HEIGHT    85
#define FRUIT_NUM       5

enum ZorderPriority {
    kFruit = 10,
    kBomb,
    };

enum FruitKind {
    kFruit1 = 0,
    kFruit2,
    kFruit3,
    kFruit4,
    kFruit5,
    };

CCPoint markPos;
int direction[4][2] = {{-1,0},{0,-1},{1,0},{0,1}};
int g_color[HORIZONTAL_NUM][VERTICAL_NUM];

#pragma ----Common Function----

bool isValidIndex(const Index& index)
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

CCPoint getPointByIndex(const Index& index)
{
    int i = index.i;
    int j = index.j;
    return ccp(i*(FRUIT_WIDTH+1)+markPos.x,j*(FRUIT_HEIGHT+1)+markPos.y);
}

Index getIndexByPoint(const CCPoint& pt)
{
    Index index = Index();
    float i = (pt.x - (markPos.x - FRUIT_WIDTH/2))/(FRUIT_WIDTH+1);
    float j = (pt.y - (markPos.y - FRUIT_HEIGHT/2))/(FRUIT_HEIGHT+1);

    if ((i < HORIZONTAL_NUM)
        && (i >= 0)
        && (j < VERTICAL_NUM)
        && (j >= 0)) {
        index.i = i;
        index.j = j;
    }
    return index;
}

bool vectorComp(const Index &index2 ,const Index &index1)
{
    if (index1.i > index2.i) {
        return true;
    }else if (index1.i == index2.i){
        if (index1.j > index2.j) {
            return true;
        }
        return false;
    }
    return false;
}

FruitObject* GameScene::getFruitByIndex(const Index& index)
{
    if (isValidIndex(index)) {
        FruitObject* fruit = (FruitObject*)getChildByTag(index.i*FRUIT_WIDTH+index.j);
        return fruit;
    }
    return NULL;
}

void GameScene::getEliminateArray(const Index& index,const unsigned int color)
{
    FruitObject *touchFruit = getFruitByIndex(index);

    if ((touchFruit->color == color)
        && (touchFruit->choose == false)
        
        ) {
        touchFruit->choose = true;
        
        for (int p = 0; p < 4; p++) {
            Index index2 = Index(index.i+direction[p][0],index.j+direction[p][1]);//{index.i+direction[p][0],index.j+direction[p][1]};
            if (isValidIndex(index2)) {
                GameScene::getEliminateArray(index2, color);
            }
        }
        
    }
}

bool GameScene::changedObject(const Index& index,const int color)
{
    CCLog("changedObject ====");
    
    return true;
}

#pragma ----Common Function----

CCScene* GameScene::scene()
{
    CCScene *sc = CCScene::create();
    CCNodeLoaderLibrary *nodeLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    nodeLibrary->registerCCNodeLoader("GameScene", GameSceneLoader::loader());
    CCBReader *ccbReader = new CCBReader(nodeLibrary);
    CCNode *node = ccbReader->readNodeGraphFromFile("ccb/GameScene");
    ccbReader->release();
    sc->addChild(node);
    return sc;
}

bool GameScene::init(){

    setTouchEnabled(1);

    memset(g_color, -1, sizeof(g_color));
//    std::vector<Index *> *pVIndex = new std::vector<Index *>;//(std::vector<Index> *)malloc(sizeof(std::vector<Index>)*1);
//    
//    for (int i = 0; i < 7; i++) {
//        Index *pIndex = new Index();
//        pIndex->i = i*i;
//        pIndex->j = i*i+100;
//        pVIndex->push_back(pIndex);
////        delete pIndex;
//    }
//    
//    for (int i = 0; i < 7; i++) {
//        Index *index = (*pVIndex)[i];
//        CCLog("init ===%d,%d",index->i,index->j);
//        delete index;
//    }
//    
//    delete pVIndex;
    
    return true;
}

void GameScene::onEnter()
{
    CCLayer::onEnter();
//    CCLog("GameScene::onEnter");
    pauseMenu->setHandlerPriority(10);
    afterloadCCB();
    layoutFruit();
    isTouch = true;
}

void GameScene::onExit()
{
    
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
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,INT_MAX,true);
}

void GameScene::pause(CCObject *pSender)
{

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
    CCPoint pt = pTouch->getLocation();
    Index index = getIndexByPoint(pt);
    CCLog("ccTouchBgan==");
//    CCLog("ccTouchBgan==%d,%d",index.i,index.j);
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

FruitObject* GameScene::fallingObject(const Index& index, const unsigned int color)
{
    char ccbName[20];
    memset(ccbName, 0, sizeof(ccbName));
    sprintf(ccbName, "ccb/fruit%d",color);
    
    FruitObject *tSprite=  FruitObject::node(ccbName, color);//(FruitObject *)addCCB(ccbName);//ccbReader->readNodeGraphFromFile(ccbName,this);//(CCNode *)node1;//
    addChild(tSprite);
    tSprite->setZOrder(kFruit);
    tSprite->setTag(index.i*FRUIT_WIDTH+index.j);
    g_color[index.i][index.j] = color;
    return tSprite;
}

void GameScene::removeFruit(const Index& index)
{
    if (isValidIndex(index)) {
        g_color[index.i][index.j] = -1;
        removeChildByTag(index.i*FRUIT_WIDTH+index.j, true);
        
        CCPoint pt = getPointByIndex(index);
        Bomb *bomb = Bomb::bomb();
        bomb->setPosition(pt);
        bomb->setZOrder(kBomb);
        addChild(bomb);
    }
}

void GameScene::layoutFruit()
{
    for (int i = 0; i < HORIZONTAL_NUM; i++) {
        for (int j = 0; j < VERTICAL_NUM; j++) {
            
            //local Object will be autorelease
            Index index = Index(i,j);
            int random = arc4random()%FRUIT_NUM;
            CCSize winSize = CCDirector::sharedDirector()->getWinSize();
            CCPoint endPos = getPointByIndex(index);
            
            FruitObject *tSprite = fallingObject(index,random);
            tSprite->setPosition(endPos.x,winSize.height);
            tSprite->endPos = endPos;       
            tSprite->scheduleOnce(schedule_selector(FruitObject::move), (i+j)*0.015);
        }
    }
}


void GameScene::removeBomb()
{
    
}

void GameScene::update(float delta)
{

}


