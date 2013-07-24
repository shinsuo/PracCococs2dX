//
//  common_function.h
//  PracCococs2dX
//
//  Created by shin on 13-7-10.
//
//

#ifndef PracCococs2dX_common_function_h
#define PracCococs2dX_common_function_h

#define DROP_INTERVAL 0.01
#define MOVE_INTERVAL 0.01
#define DELAY         0.015

#define HORIZONTAL_NUM  7
#define VERTICAL_NUM    7
#define FRUIT_WIDTH     85
#define FRUIT_HEIGHT    85
#define FRUIT_NUM       5

enum ZorderPriority {
    kFruit = 10,
    kBomb,
    kDye,
};

enum FruitKind {
    kFruit1 = 0,
    kFruit2,
    kFruit3,
    kFruit4,
    kFruit5,
};

enum ItemTag {
    kItemDye = 1000,
    kItemBomb,
};

#endif
