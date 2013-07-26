//
//  Bomb.cpp
//  PracCococs2dX
//
//  Created by shin on 13-7-11.
//
//

#include "Bomb.h"
#include "GameScene.h"

Bomb* Bomb::bomb(const char* ccbName,int flag)
{
    CCNodeLoaderLibrary *nodeLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    nodeLibrary->registerCCNodeLoader("Bomb", BombLoader::loader());
    CCBReader *ccbReader = new CCBReader(nodeLibrary);
    char _ccbName[20];
    memset(_ccbName, 0, sizeof(_ccbName));
    sprintf(_ccbName, "ccb/%s",ccbName);
    Bomb *node = (Bomb *)ccbReader->readNodeGraphFromFile(_ccbName);
    node->isAutoRemove = true;
//    node->mParent = parent;
//    node->mFlag = flag;
//    node->_callbackFunc = callbackFunc;
    ccbReader->getAnimationManager()->setAnimationCompletedCallback(node, callfunc_selector(Bomb::test));
    ccbReader->release();
    
//    CCBAnimationManager * ccbManager = (CCBAnimationManager *)node->getUserObject();
//    ccbManager->setAnimationCompletedCallback(node, callfunc_selector(Bomb::test));
    
    return node;
}

Bomb* Bomb::bomb(const char* ccbName,CCCallFuncN *callFuncN)
{
    CCNodeLoaderLibrary *nodeLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    nodeLibrary->registerCCNodeLoader("Bomb", BombLoader::loader());
    CCBReader *ccbReader = new CCBReader(nodeLibrary);
    char _ccbName[20];
    memset(_ccbName, 0, sizeof(_ccbName));
    sprintf(_ccbName, "ccb/%s",ccbName);
    Bomb *node = (Bomb *)ccbReader->readNodeGraphFromFile(_ccbName);
    node->isAutoRemove = true;
    //    node->mParent = parent;
    //    node->mFlag = flag;
    node->_callbackFuncN = callFuncN;
    ccbReader->getAnimationManager()->setAnimationCompletedCallback(node, callfunc_selector(Bomb::test));
    ccbReader->release();
    
    //    CCBAnimationManager * ccbManager = (CCBAnimationManager *)node->getUserObject();
    //    ccbManager->setAnimationCompletedCallback(node, callfunc_selector(Bomb::test));
    
    return node;
}


Bomb* Bomb::bomb(const char* ccbName,SEL_CallFuncN callBack)
{
    CCNodeLoaderLibrary *nodeLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    nodeLibrary->registerCCNodeLoader("Bomb", BombLoader::loader());
    CCBReader *ccbReader = new CCBReader(nodeLibrary);
    char _ccbName[20];
    memset(_ccbName, 0, sizeof(_ccbName));
    sprintf(_ccbName, "ccb/%s",ccbName);
    Bomb *node = (Bomb *)ccbReader->readNodeGraphFromFile(_ccbName);
    node->isAutoRemove = true;
    //    node->mParent = parent;
    //    node->mFlag = flag;
    node->_callbackFunc = callBack;
    ccbReader->getAnimationManager()->setAnimationCompletedCallback(node, callfunc_selector(Bomb::test));
    ccbReader->release();
    
    //    CCBAnimationManager * ccbManager = (CCBAnimationManager *)node->getUserObject();
    //    ccbManager->setAnimationCompletedCallback(node, callfunc_selector(Bomb::test));
    
    return node;
}

bool Bomb::init(){
//    CCLog("bomb init ====%d",mFlag);
//    _callbackFunc = NULL;
    return true;
}

void Bomb::test()
{
    if (_callbackFuncN) {
        this->runAction(_callbackFuncN);
        _callbackFuncN->release();
    }
    
    
    return;
//    if (this && _callbackFunc) {
//        (gs->*_callbackFunc)(this);
//    }
//    return;
    
    
//    if (mFlag == kItemDye) {
//        CCLog("bombRemove 1");
//        gs->dyeRemove(this);
//    }else if (mFlag == kItemBomb) {
//        CCLog("dyeRemove 1");
//        gs->bombRemove(this);
//    }
//    
//    if (isAutoRemove) {
//        removeFromParentAndCleanup(true);
//    }

    
}