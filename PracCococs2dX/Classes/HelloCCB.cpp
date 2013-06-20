//
//  HelloCCB.cpp
//  PracCococs2dX
//
//  Created by shin on 13-6-19.
//
//

#include "HelloCCB.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloCCB::scene()
{
    CCScene *sc = CCScene::create();
    CCNodeLoaderLibrary *nodeLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    nodeLibrary->registerCCNodeLoader("HelloCCB", HelloCCBLoader::loader());
    CCBReader *ccbReader = new CCBReader(nodeLibrary);
    CCNode *node = ccbReader->readNodeGraphFromFile("ccb/HelloCocosBuilder.ccbi");
    ccbReader->release();
    sc->addChild(node);
    return sc;
}

// on "init" you need to initialize your instance
bool HelloCCB::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
//    CCSprite *test = CCSprite::create("Icon-72.png");
//    addChild(test);
//    test->setPosition(ccp(100,100));
    
    return true;
}