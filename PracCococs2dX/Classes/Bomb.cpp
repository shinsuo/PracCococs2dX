//
//  Bomb.cpp
//  PracCococs2dX
//
//  Created by shin on 13-7-11.
//
//

#include "Bomb.h"

Bomb* Bomb::bomb()
{
    CCNodeLoaderLibrary *nodeLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    nodeLibrary->registerCCNodeLoader("Bomb", BombLoader::loader());
    CCBReader *ccbReader = new CCBReader(nodeLibrary);
    Bomb *node = (Bomb *)ccbReader->readNodeGraphFromFile("ccb/bomb");
    ccbReader->getAnimationManager()->setAnimationCompletedCallback(node, callfunc_selector(Bomb::test));
    ccbReader->release();
    
//    CCBAnimationManager * ccbManager = (CCBAnimationManager *)node->getUserObject();
//    ccbManager->setAnimationCompletedCallback(node, callfunc_selector(Bomb::test));
    
    return node;
}

void Bomb::test()
{
//    CCLog("removeFromParent ===");
    removeFromParent();
//    release();
}