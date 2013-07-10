//
//  PauseLayer.h
//  PracCococs2dX
//
//  Created by shin on 13-6-20.
//
//

#ifndef __PracCococs2dX__PauseLayer__
#define __PracCococs2dX__PauseLayer__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class PauseLayer:public CCLayer
,public CCBSelectorResolver
,public CCBMemberVariableAssigner
,public CCNodeLoaderListener{
    
public:
    static CCLayer* layer();
    bool init();
    void onEnter();
    void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(PauseLayer, create);
    void resume(CCObject *pSender);
    void back(CCObject *pSender);
    void restart(CCObject *pSender);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
        CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "resume:", PauseLayer::resume);
        CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "back:", PauseLayer::back);
        CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "restart:", PauseLayer::restart);
        return NULL;
    }
    
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
        
        return NULL;
    }
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "pauseLayerMenu", CCMenu *, this->pauseLayerMenu);
        return false;
    }
    
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader){
        
    }
    
private:
    CCMenu *pauseLayerMenu;
};


class PauseLayerLoader:public CCLayerLoader {
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PauseLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PauseLayer);
};

#endif /* defined(__PracCococs2dX__PauseLayer__) */
