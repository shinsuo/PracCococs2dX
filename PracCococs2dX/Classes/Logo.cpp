//
//  Logo.cpp
//  PracCococs2dX
//
//  Created by shin on 13-7-4.
//
//

#include "Logo.h"


CCNode* Logo::node()
{
    CCNodeLoaderLibrary *nodeLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    nodeLibrary->registerCCNodeLoader("Logo", LogoLoader::loader());
    CCBReader *ccbReader = new CCBReader(nodeLibrary);
    CCLayer *node = (CCLayer*)ccbReader->readNodeGraphFromFile("ccb/Logo.ccbi");
    ccbReader->release();
    return node;
}


bool Logo::init()
{
//    if (!CCLayer::init()) {
//        return false;
//    }
//    setTouchEnabled(1);
//    return true;
    return true;
}