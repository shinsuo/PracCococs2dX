//
//  GameScene.h
//  PracCococs2dX
//
//  Created by shin on 13-6-19.
//
//

#ifndef __PracCococs2dX__GameScene__
#define __PracCococs2dX__GameScene__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GameScene:public CCLayer
,public CCBSelectorResolver
,public CCBMemberVariableAssigner
,public CCNodeLoaderListener{
    
public:
    static CCScene *scene();
    bool init();
    void registerWithTouchDispatcher();
    void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GameScene, create);
    void pause(CCObject *pSender);
    void resume(CCObject *pSender);
    void back(CCObject *pSender);
    void restart(CCObject *pSender);
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
        CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "pause", GameScene::pause);
        CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "resume", GameScene::resume);
        CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "back", GameScene::back);
        CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "restart", GameScene::restart);
        return NULL;
    }
    
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
    
        return NULL;
    }
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "pauseMenu", CCMenu *, this->pauseMenu);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "fruitFlag", CCSprite *, this->fruitFlag);
        return false;
    }
    
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader){
        
    }
private:
    CCMenu *pauseMenu;
    CCSprite *fruitFlag;
    void layoutFruit();
    CCArray *fruitArray;
    CCNode* addCCB(const char* ccbName);
//    CCMenu *pauseLayerMenu;
};


class GameSceneLoader:public CCLayerLoader {
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GameSceneLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameScene);
};

#endif /* defined(__PracCococs2dX__GameScene__) */
