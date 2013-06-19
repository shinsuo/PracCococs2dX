//
//  HelloCCB.h
//  PracCococs2dX
//
//  Created by shin on 13-6-19.
//
//

#ifndef __PracCococs2dX__HelloCCB__
#define __PracCococs2dX__HelloCCB__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbBase: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
public:
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName) {
        // do nothing
        //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPlay", Playground::btnPlay);
        return NULL;
    }
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName) {
        // do nothing
        return NULL;
    }
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode) {
        // do nothing
        //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "apple", CCSprite *, this->apple);
        return NULL;
    }
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue) {
        // do nothing
        return false;
    }
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader) {
        // do nothing
    }
};

class HelloCCB : public  CcbBase{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    static CCScene* scene();
    virtual bool init();
    
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(HelloCCB, create);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
//    CREATE_FUNC(HelloCCB);
    void pause(cocos2d::CCObject *pSender){
        cocos2d::CCLog("HelloCCBLoader 2");
    }
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName) {
        // do nothing
        //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPlay", Playground::btnPlay);
        cocos2d::CCLog("HelloCCBLoader 1");
        CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "pause", HelloCCB::pause);
    }
    

};


class HelloCCBLoader : public  cocos2d::extension::CCLayerLoader{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HelloCCBLoader,loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HelloCCB);
};


#endif /* defined(__PracCococs2dX__HelloCCB__) */
