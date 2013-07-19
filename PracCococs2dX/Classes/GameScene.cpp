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
#include <algorithm>

#define HORIZONTAL_NUM  7
#define VERTICAL_NUM    7
#define FRUIT_WIDTH     85
#define FRUIT_HEIGHT    85
#define FRUIT_NUM       5

enum ZorderPriority {
    kFruit = 10,
    kBomb,
    kDye,
    };

enum FruitKind {
    kFruit1 = 0,
    kFruit2,
    kFruit3,
    kFruit4,
    kFruit5,
    };

enum ItemTag {
    kItemDye = 1000,
    kItemBomb,
    };

CCPoint markPos;
int direction[4][2] = {{-1,0},{0,-1},{1,0},{0,1}};
int g_color[HORIZONTAL_NUM][VERTICAL_NUM];
bool isSame[HORIZONTAL_NUM][VERTICAL_NUM];

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

bool isValidIJ(int i, int j)
{
    if (i < HORIZONTAL_NUM
        && (i >= 0)
        && (j < VERTICAL_NUM)
        && (j >= 0)
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

CCPoint getPointByIJ(int i,int j)
{
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
        FruitObject* fruit = (FruitObject*)getChildByTag(index.i*VERTICAL_NUM+index.j);
        return fruit;
    }
    return NULL;
}

FruitObject* GameScene::getFruitByIJ(int i, int j)
{
    if (isValidIJ(i,j)) {
        FruitObject* fruit = (FruitObject*)getChildByTag(i*VERTICAL_NUM+j);
        return fruit;
    }
    return NULL;
}

VIndex GameScene::getEliminateArray(const Index& index,const unsigned int color)
{
    VIndex eliminate;
//    FruitObject *touchFruit = getFruitByIndex(index);
//
//    if ((touchFruit->color == color)
//        && (touchFruit->choose == false)
//        
//        ) {
//        touchFruit->choose = true;
//        
//        for (int p = 0; p < 4; p++) {
//            Index index2 = Index(index.i+direction[p][0],index.j+direction[p][1]);//{index.i+direction[p][0],index.j+direction[p][1]};
//            if (isValidIndex(index2)) {
//                GameScene::getEliminateArray(index2, color);
//            }
//        }
//        
//    }
    
    if (g_color[index.i][index.j] == color
        && isSame[index.i][index.j] == false) {
        isSame[index.i][index.j] = true;
        
        eliminate.push_back(index);
        
        for (int p = 0; p < 4; p++) {
            Index index2 = Index(index.i+direction[p][0],index.j+direction[p][1]);
            if (isValidIndex(index2)) {
                VIndex tempEliminate = GameScene::getEliminateArray(index2, color);
                for (VIndex::iterator it = tempEliminate.begin(); it != tempEliminate.end(); it++) {
                    eliminate.push_back(*it);
                }
                
            }
        }
    }
    
    return eliminate;
}

bool GameScene::changedObject(const Index& index,const int color)
{
    CCLog("changedObject ====");
    for (int p = 0; p < 4; p++) {
        Index index2 = Index(index.i+direction[p][0],index.j+direction[p][1]);
        
    }
    return true;
}

bool GameScene::changedObject(const Index& index)
{
    CCLog("changedObject ====");
    int num = 1;
    FruitObject* fruiteObject = getFruitByIndex(index);
    for (int p = 0; p < 4; p++) {
        Index index2 = Index(index.i+direction[p][0],index.j+direction[p][1]);
        if (isValidIndex(index2)) {
            FruitObject* fruiteObject2 = getFruitByIndex(index2);
            if (fruiteObject2->color != fruiteObject->color) {
                removeChild(fruiteObject2, true);
                FruitObject* fruiteObject3 = fallingObject(index2, fruiteObject->color);
                fruiteObject3->setPosition(getPointByIndex(index2));
                num++;
            }else{
                num++;
            }
        }
        
        if (num >= 3) {
            break;
        }
    }
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
    isFever = true;
    
    checkEliminate();
    schedule(schedule_selector(GameScene::showEliminate), 5);
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
    VIndex vIndex;
    int i = arc4random()%4;
    int j = arc4random()%4;
    
    
    int iLength = i+4;
    int jLength = j+4;
    CCLog("pause length:%d,%d",iLength,jLength);
    for (; i < iLength; i++) {
        for (int _j=j ; _j < jLength; _j++) {
            CCLog("pause:%d,%d",i,_j);
            Index index = Index(i,_j);
            vIndex.push_back(index);
        }
    }
    
    CCLog("pause size =%d",vIndex.size());
    
    createDyes(vIndex);
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
//    CCBAnimationManager *ccbManager = (CCBAnimationManager *)getUserObject();
//    ccbManager->runAnimationsForSequenceNamed("Fever");
    
    if (isTouch) {
        CCPoint pt = pTouch->getLocation();
        Index index = getIndexByPoint(pt);
        
        FruitObject* fruitObject = getFruitByIndex(index);
        if (fruitObject) {
            
            memset(isSame, false, sizeof(isSame));
            VIndex vIndex = getEliminateArray(index, fruitObject->color);
            vector< VIndex > VVIndex;
            
            if (vIndex.size() >= 3) {
                unschedule(schedule_selector(GameScene::showEliminate));
                schedule(schedule_selector(GameScene::showEliminate), 5);
                isTouch = false;
                
//                //All Fever
                if (isFever) {
                    for (int i = 0; i < HORIZONTAL_NUM; i++) {
                        for (int j = 0; j < VERTICAL_NUM; j++) {
                            FruitObject* fruitObject4 = getFruitByIJ(i,j);
                            CCBAnimationManager *ccbManager = (CCBAnimationManager *)fruitObject4->getUserObject();
                            ccbManager->runAnimationsForSequenceNamed("Fever");
                        }
                    }
                }
                
                //sort
                sort(vIndex.begin(),vIndex.end(), vectorComp);
                
                //remove & class Vector
                for (VIndex::iterator it = vIndex.begin(); it != vIndex.end(); it++) {
                    removeFruit(*it);
                    
                    VIndex::iterator it2 = it - 1;
                    if ((it == vIndex.begin()) || (it2->i != it->i)) {
                        VIndex vIndex2;
                        vIndex2.push_back(*it);
                        VVIndex.push_back(vIndex2);
                    }else{
                        VVIndex[VVIndex.size() - 1].push_back(*it);
                    }
                }
                //remove & class Vector end
                
                //execute sequence interval
                int interval = 1;
                
                //move & drop
                for (vector< VIndex >::iterator it = VVIndex.begin(); it != VVIndex.end(); it ++) {
                    int size = it->size();
                    VIndex::iterator begin = it->begin();
                    interval = 1;
                    //move
                    for (int j = begin->j; j < VERTICAL_NUM; j++) {
                        for (int jj = j+1; jj < VERTICAL_NUM; jj++) {
                            FruitObject *fruitObject2 = getFruitByIJ(begin->i, jj);
                            if (fruitObject2) {
                                
                                fruitObject2->setTag(begin->i*VERTICAL_NUM+j);
                                g_color[begin->i][j] = fruitObject2->color;
                                fruitObject2->endPos = getPointByIJ(begin->i,j);
                                fruitObject2->move();
                                fruitObject2->scheduleOnce(schedule_selector(FruitObject::move), interval*DELAY);
                                interval++;
                                break;
                            }else{
                                continue;
                            }
                        }
                    }
                    
                    //drop
                    for (int i = size; i > 0; i--) {
                        int j = VERTICAL_NUM - i;
                        int random = arc4random()%FRUIT_NUM;
                        Index index2 = Index(begin->i,j);
                        FruitObject *fruitObject3 = fallingObject(index2, random);
                        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
                        CCPoint endPos = getPointByIndex(index2);
                        fruitObject3->setPosition(endPos.x,winSize.height);
                        fruitObject3->endPos = endPos;
                        //                    fruitObject3->move();
                        fruitObject3->scheduleOnce(schedule_selector(FruitObject::move), interval*DELAY);
                        interval++;
                    }
                    //                for (VIndex::iterator it2 = it->begin(); it2 != it->end(); it2++) {
                    //                    
                    //                }
                    
                }
                //move & drop end
                
                //All Object finish moving , check Eliminate
                scheduleOnce(schedule_selector(GameScene::checkEliminate), (interval+1)*DELAY);
            }else{
                for (VIndex::iterator it = vIndex.begin(); it != vIndex.end(); it++) {
                    FruitObject* fruitObject4 = getFruitByIndex(*it);
                    CCBAnimationManager *ccbManager = (CCBAnimationManager *)fruitObject4->getUserObject();
                    ccbManager->runAnimationsForSequenceNamed("Invalid");
                }
            }
        }
    }
    return true;
}

void GameScene::checkEliminate()
{
    //check Eliminate
    memset(isSame, false, sizeof(isSame));
    bool isEliminate =false;
    
    for (int i = 0; i < HORIZONTAL_NUM; i++) {
        for (int j = 0; j < VERTICAL_NUM; j++) {
            if (isSame[i][j] == false) {
                Index index = Index(i,j);
                FruitObject* fruitObject = getFruitByIndex(index);
                VIndex vIndex = getEliminateArray(index, fruitObject->color);
                if (vIndex.size() >= 3) {
                    isEliminate = true;
                    break;
                }
            }
        }
        if (isEliminate) {
            break;
        }
    }
    
    if (isEliminate == false) {
        int i = arc4random()%HORIZONTAL_NUM;
        int j = arc4random()%VERTICAL_NUM;
        Index index3 = Index(i,j);
        changedObject(index3);
    }
    //check Eliminate end
    isTouch = true;
}

void GameScene::showEliminate()
{
    memset(isSame, false, sizeof(isSame));
    bool isEliminate =false;
    
    int randomI = arc4random()%HORIZONTAL_NUM;
    int randomJ = arc4random()%VERTICAL_NUM;
    int direction[4][2] = {{-1,-1},{-1,1},{1,1},{1,-1}};
    
    int random = arc4random()%4;
    
    for (int p = 0; p < 4; p++) {
        random %= 4;
        for (int i = randomI; i < HORIZONTAL_NUM && i >= 0; i+=direction[random][0]) {
            for (int j = randomJ; j < VERTICAL_NUM && j >= 0; j+=direction[random][1]) {
                if (isSame[i][j] == false) {
                    Index index = Index(i,j);
                    FruitObject* fruitObject = getFruitByIndex(index);
                    VIndex vIndex = getEliminateArray(index, fruitObject->color);
                    if (vIndex.size() >= 3) {
                        for (VIndex::iterator it = vIndex.begin(); it != vIndex.end(); it++) {
                            FruitObject *fruitObject = getFruitByIndex(*it);
                            CCBAnimationManager *ccbManager = (CCBAnimationManager *)fruitObject->getUserObject();
                            ccbManager->runAnimationsForSequenceNamed("Opacity");
                        }
                        
                        isEliminate = true;
                        break;
                    }
                }
            }
            
            if (isEliminate) {
                break;
            }
        }
        
        if (isEliminate) {
            break;
        }
        
        random++;
    }
}

Bomb* GameScene::createDye(const Index& index)
{
    Bomb *tSprite = Bomb::bomb("Dye",this,callfuncN_selector(GameScene::dyeRemove));
    addChild(tSprite);
    tSprite->setZOrder(kDye);
    tSprite->setTag(kItemDye);
    tSprite->setPosition(getPointByIndex(index));
    return tSprite;
}

void GameScene::createDyes(VIndex& vIndex)
{
    for (VIndex::iterator it = vIndex.begin(); it != vIndex.end(); it++) {
        createDye(*it);
    }
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
    tSprite->setTag(index.i*VERTICAL_NUM+index.j);
    g_color[index.i][index.j] = color;
    return tSprite;
}

void GameScene::removeFruit(const Index& index)
{
    if (isValidIndex(index)) {
        g_color[index.i][index.j] = -1;
        removeChildByTag(index.i*VERTICAL_NUM+index.j, true);
        
        CCPoint pt = getPointByIndex(index);
        Bomb *bomb = Bomb::bomb("Bomb",this,callfuncN_selector(GameScene::bombRemove));
        bomb->setPosition(pt);
        bomb->setZOrder(kBomb);
        bomb->setTag(kItemBomb);
        addChild(bomb);
    }
}

void GameScene::bombRemove(CCNode *node)
{
//    removeChildByTag(kItemBomb, true);
    CCLog("bombRemove");
}

void GameScene::dyeRemove(CCNode *node)
{
//    removeChildByTag(kItemDye,true);
}

void GameScene::test()
{
    CCLog("gameScene === test");
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
            tSprite->scheduleOnce(schedule_selector(FruitObject::move), (i+j)*DELAY);
        }
    }
}

void GameScene::update(float delta)
{

}


