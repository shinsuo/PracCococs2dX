//
//  MainScene.h
//  PracCococs2dX
//
//  Created by shin on 13-6-19.
//
//

#ifndef __PracCococs2dX__MainScene__
#define __PracCococs2dX__MainScene__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MainScene :public CCLayer
,public CCBSelectorResolver
,public CCBMemberVariableAssigner
,public CCNodeLoaderListener{
    
public:
    static CCScene *scene();
    virtual bool init();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MainScene, create);
    
    void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader){
    
    }
    
    SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
        CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "guest", MainScene::guest);
        CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "start", MainScene::start);
        
        return NULL;
    }
    
    SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
        return NULL;
    }
    
    bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){
        return false;
    }
    
    void start(CCObject *pSender);
    void guest(CCObject *pSender);
};

class MainSceneLoader :public CCLayerLoader{
    
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainSceneLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainScene);
};

#endif /* defined(__PracCococs2dX__MainScene__) */
