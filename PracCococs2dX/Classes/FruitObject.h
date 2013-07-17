//
//  FruitObject.h
//  PracCococs2dX
//
//  Created by shin on 13-7-10.
//
//

#ifndef __PracCococs2dX__FruitObject__
#define __PracCococs2dX__FruitObject__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class FruitObject :public cocos2d::CCNode
,CCBSelectorResolver
,CCBMemberVariableAssigner
,CCNodeLoaderListener{
    
public:
    static FruitObject *node(const char *ccbName,int color);
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(FruitObject, create);
    virtual bool init(){return true;};
    virtual void onEnter();
    virtual void update(float delta);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName){
        return NULL;
    }
    
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
        return NULL;
    }
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode){
        return false;
    }
    
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader){
    
    }
    
    void move(float interval = 0.01f);
    
public:
    /*
        0: yellow
        1: red
        2: blue
        3: green
        4: purple
     */
    unsigned int color;
    bool choose;
    CCPoint endPos;
};

class FruitObjectLoader:public CCNodeLoader {
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(FruitObject);
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(FruitObjectLoader, loader);
};



#endif /* defined(__PracCococs2dX__FruitObject__) */
