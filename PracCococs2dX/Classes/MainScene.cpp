//
//  MainScene.cpp
//  PracCococs2dX
//
//  Created by shin on 13-6-19.
//
//

#include "MainScene.h"

bool MainScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    
    
    return true;
}

void MainScene::start(CCObject *pSender){
    CCLog("start ===");
}

void MainScene::guest(CCObject *pSender){
    CCLog("guest ===");
}