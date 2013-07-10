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

class FruitObject :public cocos2d::CCNode{
    
    
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
};



#endif /* defined(__PracCococs2dX__FruitObject__) */
