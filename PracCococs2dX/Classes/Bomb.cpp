//
//  Bomb.cpp
//  PracCococs2dX
//
//  Created by shin on 13-7-11.
//
//

#include "Bomb.h"

Bomb* Bomb::bomb(const char* ccbName,CCObject *target,SEL_CallFuncN callbackFunc)
{
    CCNodeLoaderLibrary *nodeLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    nodeLibrary->registerCCNodeLoader(ccbName, BombLoader::loader());
    CCBReader *ccbReader = new CCBReader(nodeLibrary);
    char _ccbName[20];
    memset(_ccbName, 0, sizeof(_ccbName));
    sprintf(_ccbName, "ccb/%s",ccbName);
    Bomb *node = (Bomb *)ccbReader->readNodeGraphFromFile(_ccbName);
    node->isAutoRemove = true;
    node->_callbackFunc = callbackFunc;
    ccbReader->getAnimationManager()->setAnimationCompletedCallback(node, callfunc_selector(Bomb::test));
    ccbReader->release();
    
//    CCBAnimationManager * ccbManager = (CCBAnimationManager *)node->getUserObject();
//    ccbManager->setAnimationCompletedCallback(node, callfunc_selector(Bomb::test));
    
    return node;
}

bool Bomb::init(){
    CCLog("bomb init ====");
//    _callbackFunc = NULL;
    return true;
}

void Bomb::test()
{
    if (this && _callbackFunc) {
        (this->*_callbackFunc)(this);
    }
    
    if (isAutoRemove) {
        removeFromParentAndCleanup(true);
    }
}