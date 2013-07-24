//
//  Bomb.h
//  PracCococs2dX
//
//  Created by shin on 13-7-11.
//
//

#ifndef __PracCococs2dX__Bomb__
#define __PracCococs2dX__Bomb__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class Bomb:public CCNode
//,public CCBSelectorResolver
//,public CCBMemberVariableAssigner
,public CCNodeLoaderListener{
    
public:
	static Bomb* bomb(const char* ccbName,int flag);
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Bomb, create);
    virtual bool init();
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader){}
    
    void test();
    bool isAutoRemove;
    SEL_CallFuncN _callbackFunc = NULL;
    CCNode* mParent;
    int mFlag;
};


class BombLoader:public CCNodeLoader {
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Bomb);
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(BombLoader, loader);
};

#endif /* defined(__PracCococs2dX__Bomb__) */
