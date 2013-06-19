//
//  GameScene.cpp
//  PracCococs2dX
//
//  Created by shin on 13-6-19.
//
//

#include "GameScene.h"

CCScene* GameScene::scene()
{
    CCScene *sc = CCScene::create();
    CCNodeLoaderLibrary *nodeLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    nodeLibrary->registerCCNodeLoader("GameScene", GameSceneLoader::loader());
    CCBReader *ccbReader = new CCBReader(nodeLibrary);
    CCNode *node = ccbReader->readNodeGraphFromFile("HelloCocosBuilder.ccbi");
    sc->addChild(node);
    return sc;
}

bool GameScene::init(){
    if (!CCLayer::init()) {
        return false;
    }
    
    
    
    return true;
}