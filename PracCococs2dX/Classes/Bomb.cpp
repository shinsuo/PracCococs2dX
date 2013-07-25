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
    CCLog("bomb address :%p", node);
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
    GameScene* gs = GameScene::shareScene();
    CCLog("bomb address 2:%p",this);
    if (this && _callbackFunc) {
        (gs->*_callbackFunc)(this);
    }
    return;
    
    
//    if (mFlag == kItemDye) {
//        CCLog("bombRemove 1");
//        gs->dyeRemove(this);
//    }else if (mFlag == kItemBomb) {
//        CCLog("dyeRemove 1");
        gs->bombRemove(this);
//    }
//    
    if (isAutoRemove) {
        removeFromParentAndCleanup(true);
    }

    
}