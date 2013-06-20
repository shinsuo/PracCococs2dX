//
//  HelloMenuLayer.h
//  PracCococs2dX
//
//  Created by shin on 13-6-20.
//
//

#ifndef __PracCococs2dX__HelloMenuLayer__
#define __PracCococs2dX__HelloMenuLayer__

#include "cocos2d.h"

class HelloMenuLayer : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
//    void onEnter();
//    void onExit();
    void registerWithTouchDispatcher();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCLayer* layer();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloMenuLayer);
};

#endif /* defined(__PracCococs2dX__HelloMenuLayer__) */
