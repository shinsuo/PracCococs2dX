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

CCArray *gFallingGems = NULL;
std::vector<FruitObject *> g_VObjects;
CCPoint markPos;
bool *g_BEliminate = NULL;
int direction[4][2] = {{-1,0},{0,-1},{1,0},{0,1}};

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

CCPoint getPointByIndex(const Index index)
{
    int i = index.i;
    int j = index.j;
    return ccp(i*(FRUIT_WIDTH+1)+markPos.x,j*(FRUIT_HEIGHT+1)+markPos.y);
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

FruitObject* GameScene::getFruitByIndex(Index index)
{
    FruitObject* fruit = (FruitObject*)getChildByTag(index.i*FRUIT_WIDTH+index.j);//(FruitObject *)((CCArray *)gFallingGems->objectAtIndex(index.i))->objectAtIndex(index.j);
    return fruit;
}

void GameScene::getEliminateArray(Index index,const unsigned int color)
{
    
//    Index *eliminateArray = new Index[1];
//    eliminateArray[0].i  = index.i;
//    eliminateArray[0].j  = index.j;
//    return eliminateArray;
    FruitObject *touchFruit = getFruitByIndex(index);
    CCLog("getEliminateArray:%d,%d === %d,%d",index.i,index.j,touchFruit->color,touchFruit->choose);
    if ((touchFruit->color == color)
        && (touchFruit->choose == false)
        
        ) {
        CCLog("push");
        g_Veliminate.push_back(index);
        touchFruit->choose = true;
        
        for (int p = 0; p < 4; p++) {
            Index index2 = {index.i+direction[p][0],index.j+direction[p][1]};
            if (isValidIndex(index2)) {
                GameScene::getEliminateArray(index2, color);
            }
        }
        
//        //expand to all around
//        //to left
//        Index left = {index.i-1,index.j};
//        if (isValidIndex(left)) {
//            GameScene::getEliminateArray(left,color);
//        }
//        
//        //to down
//        Index down = {index.i,index.j-1};
//        if (isValidIndex(down)) {
//            GameScene::getEliminateArray(down,color);
//        }
//        
//        //to top
//        Index top = {index.i,index.j+1};
//        if (isValidIndex(top)) {
//            GameScene::getEliminateArray(top,color);
//        }
//        
//        //to right
//        Index right = {index.i+1,index.j};
//        if (isValidIndex(right)) {
//            getEliminateArray(right,color);
//        }
    }
    
    
//    return g_Veliminate;
}

bool GameScene::changedObject(Index index,int color)
{
    
    
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
//    if (!CCLayer::init()) {
//        return false;
//    }
//
    
    CCLog("size_t vs int  ===%d,%d,%d",sizeof(size_t),sizeof(int),sizeof(bool));
    setTouchEnabled(1);
    
//    scheduleUpdate();
    
    return true;
}

void GameScene::onEnter()
{
    CCLayer::onEnter();
    CCLog("GameScene::onEnter");
    pauseMenu->setHandlerPriority(10);
    afterloadCCB();
    layoutFruit();
    isTouch = true;
    g_BEliminate = (bool *)malloc(sizeof(bool)*HORIZONTAL_NUM*VERTICAL_NUM);
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

void GameScene::onExit()
{
    free(g_BEliminate);
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
    
//    CCLayer *node = PauseLayer::layer();
//    addChild(node,20,3);
    for (int i = 0; i < HORIZONTAL_NUM; i++) {
        for (int j = 0; j < VERTICAL_NUM; j++) {
            Index index = {i,j};
            FruitObject *touchFruit = getFruitByIndex(index);
            CCLog("foreach %d,%d == %d,%d",i,j,touchFruit->color,touchFruit->choose);
        }
    }
    
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
    if (isTouch == false) {
        return false;
    }
    isTouch = false;
    CCPoint pt =  pTouch->getLocation();
//    CCLog("GameScene::ccTouchBegan ===%f,%f",pt.x,pt.y);
    Index tempIndex = getIndexByPoint(pt);
    if ((tempIndex.i == -1) || (tempIndex.j == -1)) {
        return true;
    }
//    CCLog("tempIndex ==%d,%d",tempIndex.i,tempIndex.j);
    FruitObject *touchFruit =  (FruitObject *)getChildByTag(tempIndex.i*FRUIT_WIDTH+tempIndex.j);//(FruitObject *)((CCArray *)gFallingGems->objectAtIndex(tempIndex.i))->objectAtIndex(tempIndex.j);
    getEliminateArray(tempIndex,touchFruit->color);
    
//    CCLog("eliminate size:%d",g_Veliminate.size());
    if (g_Veliminate.size() >= 3) {
        std::sort(g_Veliminate.begin(), g_Veliminate.end(), vectorComp);
        
        std::vector< std::vector<Index> > tempVIndex;
        //remove Object
        for (std::vector<Index>::iterator it = g_Veliminate.begin(); it != g_Veliminate.end(); it++) {
//            CCLog("loop a ===%d,%d",it->i,it->j);
            removeFruit(*it);
            
            if (it == g_Veliminate.begin()) {
                std::vector<Index> tempVIndex2;
                Index index = {it->i,it->j};
                tempVIndex2.push_back(index);
                tempVIndex.push_back(tempVIndex2);
            }else{
                std::vector<Index>::iterator it2 = (it-1);
                if (it2->i != it->i) {
                    std::vector<Index> tempVIndex2;
                    Index index = {it->i,it->j};
                    tempVIndex2.push_back(index);
                    tempVIndex.push_back(tempVIndex2);
                }else{
                    Index index = {it->i,it->j};
                    tempVIndex[tempVIndex.size()-1].push_back(index);
                }
            
            }
        }
        
        for (std::vector< std::vector<Index> >::iterator it = tempVIndex.begin(); it != tempVIndex.end(); it++) {
            for (std::vector<Index>::iterator it2 = it->begin(); it2 != it->end(); it2++) {
                CCLog("yeahyeah ==%d,%d,%d",it2->i,it2->j,it->size());
            }
            CCLog("again ==");
            
            std::vector<Index>::iterator it2 = it->begin();
            //moveObject
            for (int i = it2->j; i < VERTICAL_NUM; i++) {
                for (int j = i+1; j < VERTICAL_NUM; j++) {
                    Index index = {it2->i,j};
                    FruitObject *touchFruit2 = getFruitByIndex(index);
                    if (touchFruit2) {
                        index.j = i;
                        touchFruit2->setTag(index.i*FRUIT_WIDTH+index.j);
                         CCPoint endPos = getPointByIndex(index);
                        touchFruit2->endPos = endPos;//getPointByIndex(index);
                        touchFruit2->move();
                        
                        break;
                    }else{
                        continue;
                    }
                }
            }
            
            //drop Object
            for (int i = it->size(); i > 0; i--) {
                int tempJ = VERTICAL_NUM - i;
                int random = arc4random()%FRUIT_NUM;
                FruitObject *tSprite = fallingObject(random);
                tSprite->setTag(it->begin()->i*FRUIT_WIDTH+tempJ);
                Index index = {it->begin()->i,tempJ};
                CCSize winSize = CCDirector::sharedDirector()->getWinSize();
                CCPoint endPos = getPointByIndex(index);
                tSprite->setPosition(endPos.x,winSize.height);
                
                tSprite->endPos = endPos;//getPointByIndex(index);
                tSprite->move();
            }
        }
        
        //move && drop Object
//        for (std::vector<Index>::iterator it = g_Veliminate.begin(); it != g_Veliminate.end(); it++) {
//            
//            for (int currentJ = it->j; currentJ < VERTICAL_NUM; currentJ++) {
////                int nextJ = currentJ+1;
//                Index index = {it->i,currentJ};
////                FruitObject *touchFruit2 = getFruitByIndex(index);
////                if (touchFruit2) {
////                    Index index2 = {it->i,currentJ};
////                    touchFruit2->endPos = getPointByIndex(index2);
////                    touchFruit2->move();
////                }else{
////                    continue;
////                }
//                for (int nextJ = currentJ+1; nextJ < VERTICAL_NUM; nextJ++) {
//                    Index index2 = {it->i,nextJ};
//                    FruitObject *touchFruit2 = getFruitByIndex(index2);
//                    if (touchFruit2) {
//                        
//                        touchFruit2->endPos = getPointByIndex(index);
//                        touchFruit2->move();
//                        
//                        if (index.i) {
//                            <#statements#>
//                        }
//                        
//                        break;
//                    }else{
//                        continue;
//                    }
//                }
//            }
//        }
        
//        std::vector<Index>().swap(g_Veliminate);
        
//        int tempEliminate[HORIZONTAL_NUM][VERTICAL_NUM];
//        memset(tempEliminate, HORIZONTAL_NUM*VERTICAL_NUM, sizeof(int));
//        int **p = malloc(HORIZONTAL_NUM*VERTICAL_NUM*sizeof(int));
        memset(g_BEliminate, 0, sizeof(bool)*HORIZONTAL_NUM*VERTICAL_NUM);
        //check Eliminate
        int i = 0;
        int j = 0;
        for (; i < HORIZONTAL_NUM; i++) {
            for (; j < VERTICAL_NUM; j++) {
//                CCLog("bool ==%d,%d ==%d",i,j,*(g_BEliminate+i*HORIZONTAL_NUM+j));
                
                if (*(g_BEliminate+i*HORIZONTAL_NUM+j)) {
                    continue;
                }
                
                
//                if (<#condition#>) {
//                    <#statements#>
//                }
                
                Index index= {i,j};
                touchFruit = getFruitByIndex(index);
//                getEliminateArray(index,touchFruit->color);
                
            }
        }
        
        if (i == HORIZONTAL_NUM && j == VERTICAL_NUM) {
            Index index = {3,3};
            changedObject(index, 0);
        }
//        free(tempEliminate);
        
        
    }else{
        for (std::vector<Index>::iterator it = g_Veliminate.begin(); it != g_Veliminate.end(); it++) {
            Index index = {it->i,it->j};
            FruitObject *touchFruit1 =  getFruitByIndex(index);//(FruitObject *)getChildByTag(tempIndex.i*FRUIT_WIDTH+tempIndex.j);//((CCArray *)gFallingGems->objectAtIndex(tempIndex.i))->objectAtIndex(tempIndex.j);
            touchFruit1->choose = false;
            CCLog("getEliminateArray recover:%d,%d === %d,%d",it->i,it->j,touchFruit1->color,touchFruit->choose);
//            CCBAnimationManager *ccbManager = (CCBAnimationManager *)touchFruit1->getUserObject();
//            ccbManager->runAnimationsForSequenceNamed("Invalid");
        }
        
//        std::vector<Index>().swap(g_Veliminate);
    }
    
    std::vector<Index>().swap(g_Veliminate);
    
//    CCLog("vector size:%d,%d",g_Veliminate.size(),g_Veliminate.capacity());
//    g_Veliminate.clear();
    
    isTouch = true;
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
    
//    CCLog("fallingObject ==%s",ccbName);
    
    FruitObject *tSprite=  FruitObject::node(ccbName, color);//(FruitObject *)addCCB(ccbName);//ccbReader->readNodeGraphFromFile(ccbName,this);//(CCNode *)node1;//
    addChild(tSprite);
    tSprite->setZOrder(kFruit);
//    tSprite->setTag(i*FRUIT_WIDTH+j);
//    tSprite->color = color;
//    tSprite->choose = false;
//    tSprite->setPosition(ccp(i*(FRUIT_WIDTH+1)+newPt.x,j*(FRUIT_HEIGHT+1)+newPt.y));
//    ((CCArray *)gFallingGems->objectAtIndex(i))->insertObject(tSprite, j);
    return tSprite;
//    return NULL;
}

void GameScene::removeFruit(Index index)
{
//    CCNode *node =  getChildByTag(index.i*FRUIT_WIDTH+index.j);
//    CCPoint pt = node->getPosition();
//    node->removeFromParent();
    removeChildByTag(index.i*FRUIT_WIDTH+index.j, true);
//    ((CCArray *)gFallingGems->objectAtIndex(index.i))->removeObjectAtIndex(index.j);
//    FruitObject *node = (FruitObject *)((CCArray *)gFallingGems->objectAtIndex(index.i))->objectAtIndex(index.j);
//    CCNode *node1 =  addCCB("ccb/bomb");
//    addChild(node1);
//    node1->setPosition(pt);
    
    CCPoint pt = getPointByIndex(index);
    
    Bomb *bomb = Bomb::bomb();
    bomb->setPosition(pt);
    bomb->setZOrder(kBomb);
    addChild(bomb);
    
    
//    ((CCArray *)gFallingGems->objectAtIndex(index.i))->objectAtIndex(index.j);
    
//    int random = arc4random()%FRUIT_NUM;
//    FruitObject *tSprite = fallingObject(random);
//    int i = index.i;
//    int j = index.j;
//    tSprite->setTag(i*FRUIT_WIDTH+j);
//    tSprite->setPosition(ccp(i*(FRUIT_WIDTH+1)+markPos.x,j*(FRUIT_HEIGHT+1)+markPos.y));
    
//    ((CCArray *)gFallingGems->objectAtIndex(i))->insertObject(tSprite, j);
//    CCLog("removeFruit 1 ==%d,%d",tSprite->color,tSprite->choose);
//    FruitObject *node1 = (FruitObject *)((CCArray *)gFallingGems->objectAtIndex(index.i))->objectAtIndex(index.j);
//    CCLog("removeFruit 2 ==%d,%d",node1->color,node1->choose);

}

void GameScene::layoutFruit()
{
//    CCPoint pt = fruitFlag->getPosition();
//    CCPoint anchorPt = fruitFlag->getAnchorPoint();
//    CCSize size = fruitFlag->getContentSize();
//    CCPoint newPt = ccp(pt.x+(0.5-anchorPt.x)*size.width,pt.y+(0.5-anchorPt.y)*size.height);
//    CCLog("layoutFruit ===%f,%f",pt.x,pt.y);
//    CCLog("layoutFruit ===%f,%f",newPt.x,newPt.y);
//    markPos = CCPoint(newPt.x,newPt.y);
////    fruitFlag->setVisible(1);
//    fruitArray = new CCArray(FRUIT_NUM);
//    CCNodeLoaderLibrary *nodeLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
//    nodeLibrary->registerCCNodeLoader("GameScene", GameSceneLoader::loader());
//    CCBReader *ccbReader = new CCBReader(nodeLibrary);
//    CCNode *node1 = addCCB("ccb/fruit0.ccbi");//ccbReader->readNodeGraphFromFile("ccb/fruit0.ccbi",this);
//    CCNode *node2 = addCCB("ccb/fruit1.ccbi");//ccbReader->readNodeGraphFromFile("ccb/fruit1.ccbi",this);
//    CCNode *node3 = ccbReader->readNodeGraphFromFile("ccb/fruit2.ccbi",this);
//    CCNode *node4 = ccbReader->readNodeGraphFromFile("ccb/fruit3.ccbi",this);
//    CCNode *node5 = ccbReader->readNodeGraphFromFile("ccb/fruit4.ccbi",this);
//    char ccbName[20];
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
//    gFallingGems = new CCArray(HORIZONTAL_NUM);
//    for (int i = 0 ; i < HORIZONTAL_NUM; i++) {
//        gFallingGems->insertObject(new CCArray(VERTICAL_NUM),i);
//    }
    
//    CCLog("gFallingGems:%d",gFallingGems->count());
    
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
//            tSprite->setPosition(ccp(i*(FRUIT_WIDTH+1)+markPos.x,j*(FRUIT_HEIGHT+1)+markPos.y));
            Index index = {i,j};
//            tSprite->setPosition(getPointByIndex(index));
            CCSize winSize = CCDirector::sharedDirector()->getWinSize();
            CCPoint endPos = getPointByIndex(index);
            tSprite->setPosition(endPos.x,winSize.height);
            
            tSprite->endPos = endPos;//getPointByIndex(index);
            tSprite->move();
//            ((CCArray *)gFallingGems->objectAtIndex(i))->insertObject(tSprite, j);
            
//            tSprite->release();
        }
    }
}


void GameScene::removeBomb()
{
    
}

void GameScene::update(float delta)
{
    CCLog("gamescene update ===");
    for (int i = 0; i < HORIZONTAL_NUM; i++) {
        for (int j = 0; j < VERTICAL_NUM; j++) {
            CCNode* node = getChildByTag(i*FRUIT_WIDTH+j);
            if (node) {
                Index index = {i,j};
                node->setPosition(getPointByIndex(index));
            }
        }
    }
}


