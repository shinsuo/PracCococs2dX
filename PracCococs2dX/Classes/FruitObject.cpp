//
//  FruitObject.cpp
//  PracCococs2dX
//
//  Created by shin on 13-7-10.
//
//

#include "FruitObject.h"

FruitObject* FruitObject::node(const char *ccbName,int color)
{
    CCNodeLoaderLibrary *nodeLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    nodeLibrary->registerCCNodeLoader("FruitObject", FruitObjectLoader::loader());
    CCBReader *ccbReader = new CCBReader(nodeLibrary);
    FruitObject *node1 = (FruitObject *)ccbReader->readNodeGraphFromFile(ccbName);
    node1->color = color;
    node1->choose = false;
    
    ccbReader->release();
    return node1;
}


void FruitObject::onEnter()
{
    CCNode::onEnter();
//    cocos2d::CCLog("Fruite onEnter");
    
//    scheduleUpdate();
}

void FruitObject::move(float interval)
{
    CCMoveTo *moveTo = CCMoveTo::create(interval, endPos);
//    CCEaseOut *easeOut = CCEaseOut::create(moveTo, 5);
    runAction(moveTo);
}

void FruitObject::update(float delta)
{
    cocos2d::CCLog("FruiteObject");
}